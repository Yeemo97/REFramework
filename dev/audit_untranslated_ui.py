#!/usr/bin/env python3
from pathlib import Path
import re
import codecs

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
OUT = ROOT / "untranslated_core_ui.tsv"

CALLS = [
    "Text","TextWrapped","TextUnformatted","Checkbox","CheckboxFlags","Button","SmallButton",
    "RadioButton","Combo","BeginCombo","Selectable","CollapsingHeader","TreeNode","TreeNodeEx",
    "BeginTabItem","MenuItem","BeginMenu","InputText","InputTextMultiline","InputInt","InputFloat",
    "InputDouble","SliderFloat","SliderInt","SliderScalar","DragFloat","DragInt","DragScalar",
    "ColorEdit3","ColorEdit4","ColorPicker3","ColorPicker4","LabelText","BulletText","SeparatorText",
    "BeginPopupModal","BeginPopupContextItem","SetTooltip"
]
CALL_RE = re.compile(r"ImGui::(?:" + "|".join(map(re.escape, CALLS)) + r")\s*\(")
STR_RE = re.compile(r'"((?:\\.|[^"\\])*)"')
HASH_RE = re.compile(r"\{0x([0-9A-Fa-f]{8})u,")

def fnv1a32(s: str) -> int:
    h = 0x811C9DC5
    for b in s.encode("utf-8"):
        h ^= b
        h = (h * 0x01000193) & 0xFFFFFFFF
    return h

def decode_cpp_string(s: str) -> str:
    # Decode only common escapes used by UI literals, preserving unknown escapes.
    out = []
    i = 0
    while i < len(s):
        if s[i] != "\\":
            out.append(s[i]); i += 1; continue
        if i + 1 >= len(s):
            out.append("\\"); break
        c = s[i+1]
        mp = {"n":"\n","t":"\t","r":"\r",'"':'"',"\\":"\\"}
        if c in mp:
            out.append(mp[c]); i += 2
        else:
            out.append("\\" + c); i += 2
    return "".join(out)

def load_hashes():
    hashes = set()
    for p in sorted((SRC / "huawu_dict").glob("part_*.inc")):
        txt = p.read_text(encoding="utf-8")
        hashes.update(int(x, 16) for x in HASH_RE.findall(txt))
    core = (SRC / "HuawuI18NCore.hpp").read_text(encoding="utf-8")
    hashes.update(int(x, 16) for x in HASH_RE.findall(core))
    return hashes

def extract_call(src: str, start: int, limit: int = 3500) -> str:
    # Grab through first semicolon outside a quoted string.
    end = min(len(src), start + limit)
    in_str = False
    esc = False
    depth = 0
    for i in range(start, end):
        ch = src[i]
        if in_str:
            if esc:
                esc = False
            elif ch == "\\":
                esc = True
            elif ch == '"':
                in_str = False
            continue
        if ch == '"':
            in_str = True
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth = max(0, depth - 1)
        elif ch == ";" and depth == 0:
            return src[start:i+1]
    return src[start:end]

def likely_ui(text: str) -> bool:
    if not re.search(r"[A-Za-z]{2}", text):
        return False
    if text.startswith("##"):
        return False
    # Hidden suffix is still part of the ImGui label; keep it if visible prefix exists.
    visible = text.split("##", 1)[0]
    if not re.search(r"[A-Za-z]{2}", visible):
        return False
    return True

def main():
    known = load_hashes()
    found = {}
    files = [p for p in SRC.rglob("*") if p.suffix in {".cpp",".hpp",".h"}]
    files = [p for p in files if "huawu_dict" not in p.parts and p.name != "HuawuI18NCore.hpp"]

    for p in files:
        try:
            src = p.read_text(encoding="utf-8")
        except UnicodeDecodeError:
            continue
        for m in CALL_RE.finditer(src):
            call = extract_call(src, m.start())
            line = src.count("\n", 0, m.start()) + 1
            for sm in STR_RE.finditer(call):
                raw = decode_cpp_string(sm.group(1))
                if not likely_ui(raw):
                    continue
                h = fnv1a32(raw)
                if h in known:
                    continue
                rec = found.setdefault(raw, {"hash": h, "loc": set()})
                rec["loc"].add(f"{p.relative_to(ROOT)}:{line}")

    rows = []
    for text, rec in found.items():
        safe = text.replace("\t", "\\t").replace("\n", "\\n")
        rows.append((text.lower(), f"0x{rec['hash']:08X}", safe, "; ".join(sorted(rec["loc"]))))
    rows.sort()

    with OUT.open("w", encoding="utf-8", newline="\n") as f:
        f.write("hash\ttext\tlocations\n")
        for _, h, text, loc in rows:
            f.write(f"{h}\t{text}\t{loc}\n")

    print(f"Known translation hashes: {len(known)}")
    print(f"Source files scanned: {len(files)}")
    print(f"Static untranslated UI candidates: {len(rows)}")
    for _, h, text, loc in rows[:200]:
        print(f"{h}\t{text}\t{loc}")

if __name__ == "__main__":
    main()
