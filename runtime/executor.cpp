#include <cassert>
#include "executor.hpp"

namespace vm {
/* static */
Executor *Executor::CreateExecutor() {
    return new Executor;
}

/* static */
bool Executor::Destroy(Executor *executor) {
    assert(executor != nullptr);
    delete executor;
    return true;
}

std::array<VMReg, REG_NUM>& Executor::GetRegisters() {
    return regs_;
}

std::array<VMFReg, FREG_NUM>& Executor::GetFRegisters() {
    return fregs_;
}

// bool Executor::Exec(Instruction instr) {
    
// }

} // namespace vm