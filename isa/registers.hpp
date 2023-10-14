#ifndef ISA_REGISTERS_HPP
#define ISA_REGISTERS_HPP

#include <cstdint>

namespace vm {
    constexpr uint32_t REG_NUM = 21;
    constexpr uint32_t FREG_NUM = 15;

    enum Registers:uint8_t {
        ACCUM = 0x0,
        
        // integers
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

    };

    enum FRegisters:uint8_t {
        // floats
        FACCUM = 0x0,
        D1 = 0x1,
        D2 = 0x2,
        D3 = 0x3,
        D4 = 0x4,
        D5 = 0x5,
        D6 = 0x6,
        D7 = 0x7,
        D8 = 0x8,
        D9 = 0x9,
        D10 = 0xa,
        D11 = 0xb,
        D12 = 0xc,
        D13 = 0xd,
        D14 = 0xe,
    };

} // namespace vm

#endif // ISA_REGISTERS_HPP