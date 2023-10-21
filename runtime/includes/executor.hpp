#ifndef RUNTIME_INCLUDES_EXECUTOR_HPP
#define RUNTIME_INCLUDES_EXECUTOR_HPP

#include <array>
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
    std::array<VMReg, REG_NUM> &GetRegisters();
    std::array<VMFReg, FREG_NUM> &GetFRegisters();

private:
    DEFAULT_CTOR(Executor);
    DEFAULT_DESTRCTOR(Executor);

    std::array<VMReg, REG_NUM> regs_ {0};
    std::array<VMFReg, FREG_NUM> fregs_ {0};
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_EXECUTOR_HPP