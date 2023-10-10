#ifndef ISA_REGISTERS_HPP
#define ISA_REGISTERS_HPP

#include <cstdint>

namespace vm {
    constexpr uint32_t REG_NUM = 21;
    constexpr uint32_t FREG_NUM = 15;

    enum Registers:uint8_t {
        ACCUM = 0x0,
        
        // integer
        R1 = 0x1,
        R2 = 0x2,
        R3 = 0x3,
        R4 = 0x4,
        R5 = 0x5,
        R6 = 0x6,
        R7 = 0x7,
        R8 = 0x8,
        R9 = 0x9,
        R10 = 0xa,
        R11 = 0xb,
        R12 = 0xc,
        R13 = 0xd,
        R14 = 0xe,
        R15 = 0xf,
        R16 = 0x10,
        R17 = 0x11,
        R18 = 0x12,
        R19 = 0x13,
        R20 = 0x14, // PC

        // float
        D1 = 0x15,
        D2 = 0x16,
        D3 = 0x17,
        D4 = 0x18,
        D5 = 0x19,
        D6 = 0x1a,
        D7 = 0x1b,
        D8 = 0x1c,
        D9 = 0x1d,
        D10 = 0x1e,
        D11 = 0x1f,
        D12 = 0x20,
        D13 = 0x21,
        D14 = 0x22,
        D15 = 0x23,
    };
} // namespace vm

#endif // ISA_REGISTERS_HPP