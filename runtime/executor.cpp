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

// bool Executor::Exec(Instruction instr) {
    
// }

} // namespace vm