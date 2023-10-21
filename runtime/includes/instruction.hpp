#ifndef RUNTIME_INCLUDES_INSTRUCTION_HPP
#define RUNTIME_INCLUDES_INSTRUCTION_HPP

#include "types.hpp"
#include "opcodes.hpp"

/*
         _____________|_____________|_____________|_____________
               |             |             |             |
             8 bits       8 bits        8 bits        8 bits
              num        num/reg2         reg1        opcode
*/

namespace vm {
struct Instruction final {
    RegId_t GetR2() {
        return (imm >> 8);
    }
    Opcode GetInstOpcode() {
        return opc;
    }

    Opcode opc;
    RegId_t r;
    Immediate_t imm;
};

} // namespace vm

#endif // RUNTIME_INCLUDES_INSTRUCTION_HPP