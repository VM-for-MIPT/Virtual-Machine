#ifndef RUNTIME_INCLUDES_INSTRUCTION_HPP
#define RUNTIME_INCLUDES_INSTRUCTION_HPP

#include <cstdint>

/*
         ______________|______________|______________|______________
               |             |                |              |
            8 bits         8 bits           8 bits         4*8 bits
        3 bits | 5 bits      reg1             reg2          
          type | instr
*/

namespace vm {
constexpr const uint8_t INST_BIT_NUMBER = 5;
constexpr const uint8_t INST_ID_MASK = (1 << INST_BIT_NUMBER) - 1;
constexpr const uint8_t INST_TYPE_MASK = ~INST_ID_MASK;
// TODO: introduce type.hpp file with VM's typedefs
using Opcode = uint8_t;
using InstrId = uint8_t;
using TypeId = uint8_t;
// TODO: maybebaby it is better to use variable instr length (for long long)?
using Immediate = uint32_t;
using RegId = uint8_t;


struct Instruction final {
    
    InstrId GetInstId() {
        return (opc & INST_ID_MASK);
    }
    TypeId GetTypeId() {
        return (opc & INST_TYPE_MASK) >> INST_BIT_NUMBER;
    }

    Opcode opc;
    RegId r1;
    RegId r2;
    Immediate imm;
};

} // namespace vm

#endif // RUNTIME_INCLUDES_INSTRUCTION_HPP