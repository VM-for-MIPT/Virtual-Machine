#ifndef RUNTIME_INCLUDES_INSTRUCTION_HPP
#define RUNTIME_INCLUDES_INSTRUCTION_HPP

#include "types.hpp"
#include "opcodes.hpp"

/*
         ____opcode____|______________|______________|______________
               |              |              |              |
             8 bits         8 bits         8 bits         8 bits
        3 bits | 5 bits      reg1         num/reg2         num
          type | instr
*/

namespace vm {
constexpr const uint8_t INST_BIT_NUMBER = 5;
constexpr const uint8_t INST_ID_MASK = (1 << INST_BIT_NUMBER) - 1;
constexpr const uint8_t INST_TYPE_MASK = ~INST_ID_MASK;

struct Instruction final {
    InstrId_t GetInstId() {
        return (opc & INST_ID_MASK);
    }
    TypeId_t GetTypeId() {
        return (opc & INST_TYPE_MASK) >> INST_BIT_NUMBER;
    }

    Opcode opc;
    RegId_t r;
    Immediate_t imm;
};

} // namespace vm

#endif // RUNTIME_INCLUDES_INSTRUCTION_HPP