#ifndef CONFIGS_TYPES_HPP
#define CONFIGS_TYPES_HPP

#include <cstdint>

namespace vm {
using VMByte = uint8_t;
using VMReg = int64_t;
using VMFReg = double;
using VMInstr = uint32_t;

using InstrId_t = uint8_t;
using TypeId_t = uint8_t;
using RegId_t = uint8_t;
using Opcode_t = uint8_t;
using Immediate_t = int16_t;
} // namespace vm

#endif // CONFIGS_TYPES_HPP