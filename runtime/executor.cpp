#include "executor.hpp"

namespace vm {
/* static */
Executor *Executor::CreateExecutor() {
    return new Executor;
}


} // namespace vm