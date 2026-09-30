#pragma once

// Full Huawu Simplified Chinese dictionary port for REFramework Nightly 01424.
// Original localization source: Huawu MHWILDS REFramework v1.1.4 (Nightly 01240).
// 4614 entries keyed by FNV-1a 32-bit hash. C++11-compatible.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_set>

namespace huawu_i18n {

struct Entry {
    uint32_t hash;
    const char* text;
};

struct TextView {
    const char* data;
    std::size_t size;
};

inline uint32_t fnv1a32(const char* begin, const char* end) noexcept {
    uint32_t h = 0x811C9DC5u;
    if (begin == 0) {
        return h;
    }
    if (end == 0) {
        end = begin + std::strlen(begin);
    }
    for (const unsigned char* p = reinterpret_cast<const unsigned char*>(begin);
         p != reinterpret_cast<const unsigned char*>(end); ++p) {
        h ^= static_cast<uint32_t>(*p);
        h *= 0x01000193u;
    }
    return h;
}

static const Entry dict[] = {
#include "huawu_dict/part_00.inc"
#include "huawu_dict/part_01.inc"
#include "huawu_dict/part_02.inc"
#include "huawu_dict/part_03.inc"
#include "huawu_dict/part_04.inc"
#include "huawu_dict/part_05.inc"
#include "huawu_dict/part_06.inc"
#include "huawu_dict/part_07.inc"
};

inline std::size_t dict_size() noexcept {
    return sizeof(dict) / sizeof(dict[0]);
}

static const Entry extras_01424[] = {
    {0x0F746923u, "文件缺失"},
    {0x1875051Fu, "未知原因"},
    {0x393B7A01u, "启用异常文件检测器"},
    {0x473C35F7u, "应加密"},
    {0x5F529EF3u, "已加载的自定义 PAK："},
    {0x70FF8706u, "文件无效"},
    {0x775E835Fu, "允许加载 %s 目录中的 PAK 文件。文件名可自定义，但扩展名必须为 .pak（区分大小写）。"},
    {0x8255ACFDu, "重启游戏后生效。"},
    {0x866F3813u, "错误：%s"},
    {0x8AE150F7u, "显示最近记录##ShowRecentFaultyFiles"},
    {0x8F481D03u, "文件缺失"},
    {0xA0AAD9B4u, "检测到异常文件！"},
    {0xA274594Du, "检测到的异常文件总数：%zu"},
    {0xA75E65EFu, "……另有 %zu 个"},
    {0xA8C107B8u, "PAK目录加载"},
    {0xB5A63652u, "最近异常文件最大显示数量"},
    {0xB86A2F23u, "PAK 应为加密文件"},
    {0xC82ABC39u, "完整列表和详情请查看 reframework_faulty_files.txt。请使用外部工具确认是哪个 MOD/补丁导致该问题。"},
    {0xE52FBA7Au, "异常文件检测器"},
    {0xE63BDC63u, "未检测到异常文件！"},
    {0xEE58D1E6u, "文件无效"},
};

inline std::size_t extras_01424_size() noexcept {
    return sizeof(extras_01424) / sizeof(extras_01424[0]);
}

inline const char* lookup(uint32_t hash) noexcept {
    {
        const Entry* first = dict;
        const Entry* last = dict + dict_size();
        const Entry* it = std::lower_bound(
            first, last, hash,
            [](const Entry& e, uint32_t v) { return e.hash < v; });
        if (it != last && it->hash == hash) {
            return it->text;
        }
    }

    const Entry* first = extras_01424;
    const Entry* last = extras_01424 + extras_01424_size();
    const Entry* it = std::lower_bound(
        first, last, hash,
        [](const Entry& e, uint32_t v) { return e.hash < v; });
    return (it != last && it->hash == hash) ? it->text : 0;
}

inline uint32_t audit_normalized_hash(const char* begin, const char* end) noexcept {
    uint32_t h = 0x811C9DC5u;
    bool in_digits = false;
    for (const unsigned char* p = reinterpret_cast<const unsigned char*>(begin);
         p != reinterpret_cast<const unsigned char*>(end); ++p) {
        unsigned char c = *p;
        if (c >= '0' && c <= '9') {
            if (in_digits) {
                continue;
            }
            c = '#';
            in_digits = true;
        } else {
            in_digits = false;
        }
        h ^= static_cast<uint32_t>(c);
        h *= 0x01000193u;
    }
    return h;
}

inline void audit_untranslated(const char* begin, const char* end, uint32_t exact_hash) noexcept {
    if (begin == 0 || end == 0 || begin >= end) {
        return;
    }

    const std::size_t len = static_cast<std::size_t>(end - begin);
    if (len < 2 || len > 512) {
        return;
    }

    bool has_ascii_letters = false;
    for (const char* p = begin; p != end; ++p) {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
            has_ascii_letters = true;
            break;
        }
    }
    if (!has_ascii_letters) {
        return;
    }

    if (len >= 2 && begin[0] == '#' && begin[1] == '#') {
        return;
    }

    static std::unordered_set<uint32_t> seen;
    const uint32_t normalized = audit_normalized_hash(begin, end);
    if (!seen.insert(normalized).second) {
        return;
    }

    try {
        std::ofstream out{"reframework_untranslated_ui.tsv", std::ios::app | std::ios::binary};
        if (!out) {
            return;
        }

        char hashbuf[16]{};
        std::snprintf(hashbuf, sizeof(hashbuf), "0x%08X", exact_hash);
        out << hashbuf << '\t';

        for (const char* p = begin; p != end; ++p) {
            switch (*p) {
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default: out << *p; break;
            }
        }
        out << '\n';
    } catch (...) {
    }
}

inline TextView translate(const char* begin, const char* end) noexcept {
    if (begin == 0) {
        return {0, 0};
    }
    if (end == 0) {
        end = begin + std::strlen(begin);
    }
    if (begin == end) {
        return {begin, 0};
    }

    const uint32_t exact_hash = fnv1a32(begin, end);
    const char* translated = lookup(exact_hash);
    if (translated != 0) {
        return {translated, std::strlen(translated)};
    }

    audit_untranslated(begin, end, exact_hash);
    return {begin, static_cast<std::size_t>(end - begin)};
}

inline TextView translate(const char* text) noexcept {
    return translate(text, 0);
}

} // namespace huawu_i18n
