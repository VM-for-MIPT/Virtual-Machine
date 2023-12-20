#ifndef RUNTIME_INCLUDES_OBJECT_HEADER_HPP
#define RUNTIME_INCLUDES_OBJECT_HEADER_HPP

#include <cstddef>
#include <cassert>
#include "macros.hpp"
#include "types.hpp"
#include "utils.hpp"

namespace vm {
class ObjectHeader {
public:
    NO_COPY_SEMANTIC(ObjectHeader);
    NO_MOVE_SEMANTIC(ObjectHeader);

    ObjectHeader();
    explicit ObjectHeader(size_t size, Types type);
    ~ObjectHeader() = default;

    size_t GetSize() const;
    static size_t OffsetToData();
    void SetClass(Types type);
    void SetSize(size_t size);

protected:
    uint32_t markWord_;
    uint32_t klassWord_;
};
}  // namespace vm

#endif  // RUNTIME_INCLUDES_OBJECT_HEADER_HPP