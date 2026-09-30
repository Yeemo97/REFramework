#pragma once

// Full Huawu Simplified Chinese dictionary port for REFramework Nightly 01424.
// Original localization source: Huawu MHWILDS REFramework v1.1.4 (Nightly 01240).
// 4614 entries keyed by FNV-1a 32-bit hash. C++11-compatible.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

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

inline const char* lookup(uint32_t hash) noexcept {
    const Entry* first = dict;
    const Entry* last = dict + dict_size();
    const Entry* it = std::lower_bound(
        first, last, hash,
        [](const Entry& e, uint32_t v) { return e.hash < v; });
    return (it != last && it->hash == hash) ? it->text : 0;
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

    const char* translated = lookup(fnv1a32(begin, end));
    if (translated != 0) {
        return {translated, std::strlen(translated)};
    }
    return {begin, static_cast<std::size_t>(end - begin)};
}

inline TextView translate(const char* text) noexcept {
    return translate(text, 0);
}

} // namespace huawu_i18n
