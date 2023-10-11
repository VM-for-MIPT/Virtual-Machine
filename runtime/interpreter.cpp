#include <cassert>
#include "interpreter.hpp"

namespace vm {
Interpreter::Interpreter() {
    decoder_ = Decoder::CreateDecoder();
    executor_ = Executor::CreateExecutor();
}
Interpreter::~Interpreter() {
    bool success = Decoder::Destroy(decoder_);
    success &= Executor::Destroy(executor_);
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

void Run(VMByte* code) {
    
}

} // namespace vm 