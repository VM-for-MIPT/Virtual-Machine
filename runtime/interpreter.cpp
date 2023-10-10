#include <cassert>
#include "interpreter.hpp"

namespace vm {
Interpreter::Interpreter() {
    decoder_ = Decoder::CreateDecoder();
    executor_ = Executor::CreateExecutor();
}
Interpreter::~Interpreter() {
    bool success = Decoder::Destroy(decoder_);
    assert(success);
}

/* static */
Interpreter *Interpreter::CreateInterpreter() {
    return new Interpreter;
}

/* static */
bool Interpreter::Destroy(Interpreter *interpreter) {
    assert(interpreter != nullptr);
    delete interpreter;
    return true;
}

} // namespace vm 