#ifndef ISA_OPCODES_HPP
#define ISA_OPCODES_HPP

#include <cstdint>

namespace vm {
    constexpr uint32_t INSTR_NUM = 30;

    enum Opcode:uint8_t {
        RESERVED = 0x0,

        // integer
        IADD = 0x1,
        ISUB = 0x2,
        IMUL = 0x3,
        IDIV = 0x4,

        // float
        FADD = 0x5,
        FSUB = 0x6,
        FMUL = 0x7,
        FDIV = 0x8,

        // logic
        AND = 0x9,
        OR = 0xa,
        XOR = 0xb,

        // integer
        EQ = 0xc,
        NE = 0xd,
        LT = 0xe,       // less
        LE = 0xf,       // less or equal
        GT = 0x10,      // greater
        GE = 0x11,      // greater or equal

        // float
        FEQ = 0x12,
        FNE = 0x13,
        FLT = 0x14,      // less
        FLE = 0x15,      // less or equal
        FGT = 0x16,      // greater
        FGE = 0x17,      // greater or equal

        // internal
        ISCAN = 0x18,
        FSCAN = 0x19,
        IPRINT = 0x1a,
        FPRINT = 0x1b,
        SIN = 0x1c,
        COS = 0x1d
    };

} // namespace vm

#endif // ISA_OPCODES_HPP