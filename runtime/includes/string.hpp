#ifndef RUNTIME_INCLUDES_STRING_HPP
#define RUNTIME_INCLUDES_STRING_HPP

#include <cstddef>
#include <cassert>
#include "macros.hpp"
#include "utils.hpp"

namespace vm {
class String final {
public:
    NO_COPY_SEMANTIC(String);
    NO_MOVE_SEMANTIC(String);

    [[nodiscard]] static String *CreateString(void *mem, size_t size);
    static bool Destroy(String *String);

    int GetValueByIdx(int idx);
    void SetValueByIdx(int value, int idx);

private:
    void *ptr_;
    uint32_t MarkWord_;   // for the future
    uint32_t KlassWord_;  // what type

    size_t GetOffsetByIdx(int idx);

    String(void *mem, size_t size)
    {
        MarkWord_ = size;
        ptr_ = mem;
    };
    String();
    ~String();
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_STRING_HPP