#include "object_header.hpp"

namespace vm {
ObjectHeader::ObjectHeader(size_t size, Types type)
{
    markWord_ = size;
    klassWord_ = type;
}

ObjectHeader::ObjectHeader()
{
    markWord_ = 0;
    klassWord_ = 0;
}

size_t ObjectHeader::GetSize() const
{
    return markWord_;
}

/* static */
size_t ObjectHeader::OffsetToData()
{
    return sizeof(markWord_) + sizeof(klassWord_);
}

void ObjectHeader::SetClass(Types type)
{
    klassWord_ = type;
}

void ObjectHeader::SetSize(size_t size)
{
    markWord_ = size;
}
}  // namespace vm