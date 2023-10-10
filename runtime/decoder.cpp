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
    
    return Instruction();
}

} // namespace vm 