#include "array.hpp"

namespace vm {
/* static */
Array *Array::CreateArray(size_t size, void *mem)
{
    auto arr = new Array(size, mem);
    return arr;
}

/* static */
bool Array::Destroy(Array *array)
{
    assert(array != nullptr);
    delete array;
    return true;
}

size_t Array::GetOffsetByIdx(int idx)
{
    return idx * KlassWord_;
}

}  // namespace vm
