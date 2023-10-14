#include <cassert>
#include "decoder.hpp"
#include "opcodes.hpp"

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
    Opcode opc = static_cast<Opcode>(operation & 7);
    RegId_t r = ((operation >> 8) & 7);
    uint32_t upper_value = ((operation >> 16) & 7);
    uint32_t lower_value = (operation >> 24);
    Immediate_t imm = (upper_value << 8) + lower_value;
    return {opc, r, imm};
}
} // namespace vm