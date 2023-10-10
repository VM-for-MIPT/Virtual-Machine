#ifndef RUNTIME_INCLUDES_DECODER_HPP
#define RUNTIME_INCLUDES_DECODER_HPP

#include "instruction.hpp"
#include "macros.hpp"

namespace vm {
class Decoder final {
 public:
    NO_COPY_SEMANTIC(Decoder);
    NO_MOVE_SEMANTIC(Decoder);

    [[nodiscard]] static Decoder *CreateDecoder();
    static bool Destroy(Decoder *decoder);
    Instruction Decode(VMInstr operation);
 private:
    Decoder();
    ~Decoder();
};
} // namespace vm

#endif // RUNTIME_INCLUDES_DECODER_HPPN