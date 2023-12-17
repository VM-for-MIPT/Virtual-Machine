#ifndef RUNTIME_INCLUDES_VM_FILE_HPP
#define RUNTIME_INCLUDES_VM_FILE_HPP

#include <cassert>
#include <tuple>
#include <variant>
#include <vector>
#include "types.hpp"

namespace vm {
class VMFile final {
public:
    NO_DEFAULT_CTOR(VMFile);
    DEFAULT_DESTRCTOR(VMFile);
    explicit VMFile(VMByte *runnable_code, std::vector<std::tuple<Types, size_t, void *>> const_pool)
        : code_(runnable_code), const_pool_(const_pool)
    {
    }

    template <typename T>
    inline T GetConst(size_t ind)
    {
        assert(ind < const_pool_.size());
        auto val = std::get<2>(const_pool_[ind]);
        return *reinterpret_cast<T *>(val);
    }

    VMByte *GetCode() const
    {
        return code_;
    }

private:
    VMByte *code_;
    std::vector<std::tuple<Types, size_t, void *>> const_pool_;
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_VM_FILE_HPP