#ifndef RUNTIME_INCLUDES_INTERPRETER_HPP
#define RUNTIME_INCLUDES_INTERPRETER_HPP

#include "decoder.hpp"
#include "executor.hpp"

namespace vm {

class Interpreter final {
 public:
    NO_COPY_SEMANTIC(Interpreter);
    NO_MOVE_SEMANTIC(Interpreter);

    [[nodiscard]] static Interpreter *CreateInterpreter();
    static bool Destroy(Interpreter *);
    VMInstr FetchNext();
    //TODO: move to VM class
    void Run(VMByte* code);
 private:
    Interpreter();
    ~Interpreter();
    void MovePC();

    Decoder* decoder_;
    Executor* executor_;
};

} // namespace vm

#endif //RUNTIME_INCLUDES_INTERPRETER_HPP