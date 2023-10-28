#ifndef RUNTIME_INCLUDES_INTERPRETER_HPP
#define RUNTIME_INCLUDES_INTERPRETER_HPP

#include <cmath>
#include <stdexcept>

#include "decoder.hpp"
#include "executor.hpp"
#include "vm_file.hpp"

namespace vm {
class Interpreter final {
public:
    NO_COPY_SEMANTIC(Interpreter);
    NO_MOVE_SEMANTIC(Interpreter);
    NO_DEFAULT_CTOR(Interpreter);

    [[nodiscard]] static Interpreter *CreateInterpreter(VMFile *vm_file);
    static bool Destroy(Interpreter *);
    VMInstr FetchNext(VMByte *code, VMReg pc);
    // TODO: move to VM class
    void Run();

private:
    Interpreter(VMFile *vm_file);
    ~Interpreter();

    Decoder *decoder_;
    Executor *executor_;
    VMFile *vm_file_;
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_INTERPRETER_HPP