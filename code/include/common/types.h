#pragma once

#include <cmath>
#include <cstdint>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;
using size_t = std::size_t;

static_assert(sizeof(u16) == sizeof(short));
static_assert(sizeof(u32) == sizeof(int));

/*
 * A function reached only from assembly, so nothing in C++ references it. The
 * practice tool also forced these into .init for --gc-sections, which this
 * build does not pass and mm.ld does not declare.
 */
#define RST_HOOK [[gnu::used]]
