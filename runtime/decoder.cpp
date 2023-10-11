#include <cassert>
#include "decoder.hpp"

namespace vm {
Decoder::Decoder() = default;
Decoder::~Decoder() = default;

/* static */
Decoder *Decoder::CreateDecoder() {
    return new Decoder;
}

/* static */
bool Decoder::Destroy(Decoder *decoder) {
    assert(decoder != nullptr);
    delete decoder;
    return true;
}

Instruction Decoder::Decode(VMInstr operation) {
    Opcode_t opc = operation >> 24;
    RegId_t r = (operation >> 16) & ~(TwoPow<16>() - TwoPow<8>());
    Immediate_t imm = operation & ((1 << 16) - 1);

    Instruction instr {opc, r, imm};
    return instr;
}

} // namespace vm