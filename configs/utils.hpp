#ifndef CONFIGS_UTILS_HPP
#define CONFIGS_UTILS_HPP

#include <cstdint>

namespace vm {
template <uint32_t power>
constexpr uint64_t TwoPow()
{
    static_assert(power >= 0, "Power must be non-negative");
    if constexpr (power == 0) {
        return 1;
    } else {
        return TwoPow<power - 1>() * 2;
    }
}

template <uint32_t power>
constexpr uint64_t TenPow()
{
    static_assert(power >= 0, "Power must be non-negative");
    if constexpr (power == 0) {
        return 1;
    }
    else {
        return TenPow<power - 1>() * 10;
    }
}

template <uint64_t shift, int32_t float_count, uint64_t V>
constexpr uint64_t GetShiftedMemoryValue()
{
    if constexpr (float_count > 0) {
        return static_cast<uint64_t>(V * (1ULL << shift) / TenPow<float_count - 1>());
    }

    return static_cast<uint64_t>(V * (1ULL << shift) / TenPow<0>());
}

template <uint64_t shift, int32_t float_count, uint64_t V, char C, char... Cs>
constexpr uint64_t GetShiftedMemoryValue()
{
    static_assert(C == '.' || (C >= '0' && C <= '9'), "Using not a number");
    if constexpr (C == '.') {
        return GetShiftedMemoryValue<shift, 1, V, Cs...>();
    } else if constexpr (float_count > 0) {
        return GetShiftedMemoryValue<shift, float_count + 1, V * 10 + C - '0', Cs...>();
    }

    return GetShiftedMemoryValue<shift, float_count, V * 10 + C - '0', Cs...>();
}

constexpr uint64_t SHIFT_KB = 10ULL;
constexpr uint64_t SHIFT_MB = 20ULL;
constexpr uint64_t SHIFT_GB = 30ULL;

template <char... Cs>
constexpr uint64_t operator"" _KB()
{
    static_assert(sizeof...(Cs) <= 20);
    return GetShiftedMemoryValue<SHIFT_KB, 0, 0, Cs...>();
}
template <char... Cs>
constexpr uint64_t operator"" _MB()
{
    static_assert(sizeof...(Cs) <= 20);
    return GetShiftedMemoryValue<SHIFT_MB, 0, 0, Cs...>();
}
template <char... Cs>
constexpr uint64_t operator"" _GB()
{
    static_assert(sizeof...(Cs) <= 20);
    return GetShiftedMemoryValue<SHIFT_GB, 0, 0, Cs...>();
}

template <typename T>
constexpr uintptr_t ToUintPtr(T *ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

constexpr uintptr_t ToUintPtr(std::nullptr_t)
{
    return ToUintPtr(static_cast<void *>(nullptr));
}

template <typename T>
constexpr T *ToNativePtr(uintptr_t ptr)
{
    return reinterpret_cast<T *>(ptr);
}

inline void *ToVoidPtr(uintptr_t ptr)
{
    return reinterpret_cast<void *>(ptr);
}
} // namespace vm

#endif  // CONFIGS_UTILS_HPP