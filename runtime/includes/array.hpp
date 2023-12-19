#ifndef RUNTIME_INCLUDES_ARRAY_HPP
#define RUNTIME_INCLUDES_ARRAY_HPP

#include <stdint.h>
#include <cstdlib>
#include "utils.hpp"

namespace vm {
class Array final {
public:
    NO_COPY_SEMANTIC(Array);
    NO_MOVE_SEMANTIC(Array);


    [[nodiscard]] static Array *CreateArray(void* mem, size_t size);
    static bool Destroy(Array *array);

    int GetValueByIdx(int idx);
    int SetValueByIdx(int value, int idx);

private:
    void* ptr_;
    uint32_t MarkWord_;   // for the future
    uint32_t KlassWord_;  // what type

    size_t GetOffsetByIdx(int idx);

    // Array(void* mem, size_t size)
    // {
    //     MarkWord_ = size;
    //     ptr_ = mem;
    // };
    Array();
    ~Array();
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_ARRAY_HPP