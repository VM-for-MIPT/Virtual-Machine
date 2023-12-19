#include "frame.hpp"

namespace vm::mem {
Frame::Frame(size_t size)
{
    uint8_t *mem = new uint8_t[size];  // TODO(Mirageinvo): allocator alloc
    assert(mem != nullptr);
    start_ = ToUintPtr<uint8_t>(mem);
    cur_ = start_ + CalculateBytesForRegisters();
    end_ = start_ + size;
}

Frame::~Frame()
{
    delete[] ToNativePtr<uint8_t>(start_);
}

/* static */
Frame *Frame::GetCurrent()
{
    return instance_;
}

/* static */
Frame *Frame::CreateNew()
{
    Frame *new_frame = new Frame();
    frames_.push_back(new_frame);
    instance_ = new_frame;
    return instance_;
}

/* static */
Frame *Frame::DeleteLast()
{
    delete instance_;
    frames_.pop_back();
    [[unlikely]] if (frames_.size() == 0)
    {
        // final frame; exiting the program
        instance_ = nullptr;
    }
    else
    {
        instance_ = frames_[frames_.size() - 1];
    }
}

/* static */
std::vector<Frame *> *Frame::GetFrames()
{
    return &Frame::frames_;
}

void *Frame::GetRegPtr(size_t reg_id)
{
    assert(reg_id < INT_REGS_NUM + DOUBLE_REGS_NUM);
    return ToVoidPtr(start_ + (reg_id * sizeof(int64_t)));
}

void *Frame::GetRawMem()
{
    return ToVoidPtr(start_);
}

void *Frame::GetFreeMemPtr(size_t size)
{
    void *mem = ToVoidPtr(cur_);
    cur_ += size;
    assert(cur_ <= end_);
    return mem;
}

void Frame::SetUpForCall(size_t num_of_args, int64_t jump_offset, int64_t pc, void *prev_fr_mem)
{
    std::memcpy(ToVoidPtr(start_), prev_fr_mem, num_of_args * sizeof(VMReg));
}

constexpr size_t Frame::CalculateBytesForRegisters() const
{
    // currently all registers are of 64 bits size
    // by default it's allocated 21 int registers and 15 float registers
    return sizeof(int64_t) * (INT_REGS_NUM + DOUBLE_REGS_NUM);
}
}  // namespace vm::mem