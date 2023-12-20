#include "string.hpp"

namespace vm {
String::String() = default;
String::~String() = default;

/* static */
String *String::CreateString(void *mem, size_t size)
{
    String *arr = new String(mem, size);
    return arr;
}

/* static */
bool String::Destroy(String *string)
{
    assert(string != nullptr);
    delete string;
    return true;
}

size_t String::GetOffsetByIdx(int idx)
{
    return idx * KlassWord_;
}

int String::GetValueByIdx(int idx)
{
    return *ToNativePtr<int64_t>(ToUintPtr(ptr_) + GetOffsetByIdx(idx));
}

void String::SetValueByIdx(int value, int idx)
{
    auto idx_pointer = ToUintPtr(ptr_) + GetOffsetByIdx(idx);
    *ToNativePtr<int64_t>(idx_pointer) = value;
}

}  // namespace vm
