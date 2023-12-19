#include "array.hpp"

namespace vm {
Array::Array() = default;
Array::~Array() = default;

/* static */
Array *Array::CreateArray(void *mem, size_t size)
{
    Array *arr = new Array(mem, size);
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

int Array::GetValueByIdx(int idx)
{
    return *ToNativePtr<int64_t>(ToUintPtr(ptr_) + GetOffsetByIdx(idx));
}

void Array::SetValueByIdx(int value, int idx)
{
    auto idx_pointer = ToUintPtr(ptr_) + GetOffsetByIdx(idx);
    *ToNativePtr<int64_t>(idx_pointer) = value;
}

}  // namespace vm
