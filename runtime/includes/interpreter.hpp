#ifndef RUNTIME_INCLUDES_INTERPRETER_HPP
#define RUNTIME_INCLUDES_INTERPRETER_HPP

#include "decoder.hpp"

namespace vm {

class Interpreter final {
 public:
    NO_COPY_SEMANTIC(Interpreter);
    NO_MOVE_SEMANTIC(Interpreter);

    [[nodiscard]] static Interpreter *CreateInterpreter();
    static bool Destroy(Interpreter *);
 private:
    Interpreter();
    ~Interpreter();

    Decoder* decoder_;
};

} // namespace vm

#endif //RUNTIME_INCLUDES_INTERPRETER_HPP