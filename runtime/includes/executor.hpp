#ifndef RUNTIME_INCLUDES_EXECUTOR_HPP
#define RUNTIME_INCLUDES_EXECUTOR_HPP

#include "executor.hpp"
#include "instruction.hpp"
#include "opcodes.hpp"
#include "macros.hpp"
#include "registers.hpp"
#include "types.hpp"

namespace vm {
class Executor final {
 public:
    NO_COPY_SEMANTIC(Executor);
    NO_MOVE_SEMANTIC(Executor);

    [[nodiscard]] static Executor *CreateExecutor();
    static bool Destroy(Executor *);
    bool Exec(Instruction);
 private:
    DEFAULT_CTOR(Executor);
    DEFAULT_DESTRCTOR(Executor);

    VMReg regs[REG_NUM];
    VMFReg fregs[FREG_NUM];
};
} // namespace vm

#endif //RUNTIME_INCLUDES_EXECUTOR_HPP