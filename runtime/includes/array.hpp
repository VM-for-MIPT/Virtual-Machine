#ifndef RUNTIME_INCLUDES_ARRAY_HPP
#define RUNTIME_INCLUDES_ARRAY_HPP

#include <cstddef>
#include <cassert>
#include "macros.hpp"
#include "utils.hpp"
#include "object_header.hpp"

namespace vm {
class Array final : ObjectHeader {
public:
    NO_COPY_SEMANTIC(Array);
    NO_MOVE_SEMANTIC(Array);

    [[nodiscard]] static Array *CreateArray(void *mem, size_t length, Types type);
    static bool Destroy(Array *array);
    static size_t ComputeSize(size_t length, Types type);

    int64_t GetValueByIdx(size_t idx);
    void SetValueByIdx(int64_t value, size_t idx);
    static int64_t GetElementSize(Types type);
    int64_t GetElementSize();

private:
    size_t GetOffsetByIdx(size_t idx);

    Array();
    ~Array();
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_ARRAY_HPP