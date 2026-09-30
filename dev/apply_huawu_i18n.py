#!/usr/bin/env python3
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
IMGUI = ROOT / "dependencies" / "imgui"
HEADER_INCLUDE = '#include "../../src/HuawuI18NCore.hpp"\n'

def add_include(path: Path):
    text = path.read_text(encoding="utf-8")
    if HEADER_INCLUDE in text:
        return
    marker = '#include "imgui.h"\n#ifndef IMGUI_DISABLE\n#include "imgui_internal.h"\n'
    if text.count(marker) != 1:
        raise RuntimeError(f"{path}: include anchor not found uniquely")
    replacement = '#include "imgui.h"\n#ifndef IMGUI_DISABLE\n#include "imgui_internal.h"\n' + HEADER_INCLUDE
    path.write_text(text.replace(marker, replacement, 1), encoding="utf-8", newline="\n")

def replace_once(path: Path, old: str, new: str):
    text = path.read_text(encoding="utf-8")
    count = text.count(old)
    if count != 1:
        raise RuntimeError(f"{path}: expected exactly one match, got {count}: {old[:100]!r}")
    path.write_text(text.replace(old, new, 1), encoding="utf-8", newline="\n")
    print(f"[OK] patched {path.relative_to(ROOT)}")

p = IMGUI / "imgui.cpp"
add_include(p)
replace_once(
    p,
    """    ImFont* font = g.Font;
    const float font_size = g.FontSize;
    if (text == text_display_end)
        return ImVec2(0.0f, font_size);
    ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, wrap_width, text, text_display_end, NULL);
""",
    """    ImFont* font = g.Font;
    const float font_size = g.FontSize;
    if (text == text_display_end)
        return ImVec2(0.0f, font_size);

    const auto huawu_text = huawu_i18n::translate(text, text_display_end);
    text = huawu_text.data;
    text_display_end = huawu_text.data + huawu_text.size;

    ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, wrap_width, text, text_display_end, NULL);
"""
)

p = IMGUI / "imgui_draw.cpp"
add_include(p)
replace_once(
    p,
    """    font->RenderText(this, font_size, pos, col, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
""",
    """    const auto huawu_text = huawu_i18n::translate(text_begin, text_end);
    text_begin = huawu_text.data;
    text_end = huawu_text.data + huawu_text.size;
    font->RenderText(this, font_size, pos, col, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
"""
)

p = IMGUI / "imgui_widgets.cpp"
add_include(p)

replace_once(
    p,
    """    const char* text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    TextEx(text, text_end, ImGuiTextFlags_NoWidthForLargeClippedText);
""",
    """    const auto huawu_fmt = huawu_i18n::translate(fmt);
    fmt = huawu_fmt.data;
    const char* text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    TextEx(text, text_end, ImGuiTextFlags_NoWidthForLargeClippedText);
"""
)

replace_once(
    p,
    """    const char* value_text_begin, *value_text_end;
    ImFormatStringToTempBufferV(&value_text_begin, &value_text_end, fmt, args);
    const ImVec2 value_size = CalcTextSize(value_text_begin, value_text_end, false);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
""",
    """    const auto huawu_fmt = huawu_i18n::translate(fmt);
    fmt = huawu_fmt.data;
    const auto huawu_label = huawu_i18n::translate(label);
    const char* value_text_begin, *value_text_end;
    ImFormatStringToTempBufferV(&value_text_begin, &value_text_end, fmt, args);
    const ImVec2 value_size = CalcTextSize(value_text_begin, value_text_end, false);
    const ImVec2 label_size = CalcTextSize(huawu_label.data, huawu_label.data + huawu_label.size, true);
"""
)

replace_once(
    p,
    """    if (label_size.x > 0.0f)
        RenderText(ImVec2(value_bb.Max.x + style.ItemInnerSpacing.x, value_bb.Min.y + style.FramePadding.y), label);
""",
    """    if (label_size.x > 0.0f)
        RenderText(ImVec2(value_bb.Max.x + style.ItemInnerSpacing.x, value_bb.Min.y + style.FramePadding.y), huawu_label.data, huawu_label.data + huawu_label.size);
"""
)

replace_once(
    p,
    """    const char* text_begin, *text_end;
    ImFormatStringToTempBufferV(&text_begin, &text_end, fmt, args);
    const ImVec2 label_size = CalcTextSize(text_begin, text_end, false);
""",
    """    const auto huawu_fmt = huawu_i18n::translate(fmt);
    fmt = huawu_fmt.data;
    const char* text_begin, *text_end;
    ImFormatStringToTempBufferV(&text_begin, &text_end, fmt, args);
    const ImVec2 label_size = CalcTextSize(text_begin, text_end, false);
"""
)

replace_once(
    p,
    """    const char* text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    const ImVec2 text_size = CalcTextSize(text, text_end);
""",
    """    const auto huawu_fmt = huawu_i18n::translate(fmt);
    fmt = huawu_fmt.data;
    const char* text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    const ImVec2 text_size = CalcTextSize(text, text_end);
"""
)

print("[DONE] Huawu core i18n hooks applied to Dear ImGui submodule.")
