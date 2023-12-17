#ifndef RUNTIME_INCLUDES_FRAME_HPP
#define RUNTIME_INCLUDES_FRAME_HPP

#include <cstddef>
#include <vector>
#include <cassert>
#include "utils.hpp"

namespace vm::mem {
class Frame final {
public:
    static constexpr size_t INT_REGS_NUM = 21;
    static constexpr size_t DOUBLE_REGS_NUM = 15;
    explicit Frame(size_t size = 1_KB);
    ~Frame();
    static Frame *GetCurrent();
    static void CreateNew();
    static void DeleteLast();
    static std::vector<Frame *> *GetFrames();
    void *GetRegPtr(size_t reg_id);
    void *GetFreeMemPtr(size_t size);

private:
    constexpr size_t CalculateBytesForRegisters() const;
    inline static Frame *instance_;
    inline static std::vector<Frame *> frames_;
    uintptr_t start_;
    uintptr_t cur_;  // always != start_ since registers are allocated
    uintptr_t end_;  // if cur_ == end_ there is no memory left
};
}  // namespace vm::mem

#endif  // RUNTIME_INCLUDES_FRAME_HPP