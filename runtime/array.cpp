#include "array.hpp"

namespace vm {
Array::Array() = default;
Array::~Array() = default;

/* static */
Array* Array::CreateArray(void* mem, size_t size)
{
    Array* arr = new (mem) Array;
    return arr;
}

/* static */
static bool Array::Destroy(Array *array)
{
    assert(array != nullptr);
    delete array;
    return true;
}

size_t Array::GetOffsetByIdx(int idx)
{
    return idx * KlassWord_;
}

int Array::GetValueByIdx(int idx) {
  return *(ptr_ + GetOffsetByIdx(idx));
}

int Array::SetValueByIdx(int value, int idx) {
  auto idx_pointer = ptr_ + GetOffsetByIdx(idx);
  *idx_pointer = value;
}

}  // namespace vm
