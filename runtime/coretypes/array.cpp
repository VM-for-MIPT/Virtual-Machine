#include "array.hpp"

namespace vm {
Array::Array() = default;
Array::~Array() = default;

/* static */
Array *Array::CreateArray(void *mem, size_t length, Types type)
{
    Array *arr = static_cast<Array *>(mem);
    arr->SetClass(type);
    arr->SetSize(length);
    return arr;
}

/* static */
bool Array::Destroy(Array *array)
{
    assert(array != nullptr);
    delete array;
    return true;
}

/* static */
size_t Array::ComputeSize(size_t length, Types type)
{
    return OffsetToData() + (GetElementSize(type) * length);
}

size_t Array::GetOffsetByIdx(size_t idx)
{
    return idx * GetElementSize(static_cast<Types>(klassWord_));
}

int64_t Array::GetValueByIdx(size_t idx)
{
    return *ToNativePtr<int64_t>(ToUintPtr(this) + OffsetToData() + GetOffsetByIdx(idx));
}

void Array::SetValueByIdx(int64_t value, size_t idx)
{
    auto idx_pointer = ToUintPtr(this) + OffsetToData() + GetOffsetByIdx(idx);
    *ToNativePtr<int64_t>(idx_pointer) = value;
}

/* static */
int64_t Array::GetElementSize(Types type)
{
    switch (type) {
        case Types::CHAR:
            return sizeof(char);
        case Types::DOUBLE:
            return sizeof(double);
        case Types::INT:
            return sizeof(int64_t);
        default:
            assert(false);  // Should be unreachable
    }
}

int64_t Array::GetElementSize()
{
    switch (static_cast<Types>(klassWord_)) {
        case Types::CHAR:
            return sizeof(char);
        case Types::DOUBLE:
            return sizeof(double);
        case Types::INT:
            return sizeof(int64_t);
        default:
            assert(false);  // Should be unreachable
    }
}

}  // namespace vm
