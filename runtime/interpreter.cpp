#include <iostream>
#include <cassert>
#include "interpreter.hpp"
#include "frame.hpp"
#include "registers.hpp"
#include "array.hpp"

namespace vm {
using mem::Frame;

Interpreter::Interpreter(VMFile *vm_file) : vm_file_(vm_file)
{
    decoder_ = Decoder::CreateDecoder();
}
Interpreter::~Interpreter()
{
    [[maybe_unused]] bool success = Decoder::Destroy(decoder_);
    assert(success);
    delete vm_file_;
}

/* static */
Interpreter *Interpreter::CreateInterpreter(VMFile *vm_file)
{
    return new Interpreter(vm_file);
}

/* static */
bool Interpreter::Destroy(Interpreter *interpreter)
{
    assert(interpreter != nullptr);
    delete interpreter;
    return true;
}

VMInstr Interpreter::FetchNext(VMByte *code, VMReg pc)
{
    return *reinterpret_cast<VMInstr *>(&code[pc]);
}

void Interpreter::Run(size_t entrypoint)
{
    VMByte *code = vm_file_->GetCode();
    assert(Frame::GetFrames()->size() == 0);
    Frame::CreateNew();
    auto frame = Frame::GetCurrent();
    assert(frame != nullptr);
    assert(Frame::GetFrames()->size() != 0);
    VMReg pc = entrypoint;
    static void *dispatch_table[] = {&&exit,  &&iadd,  &&isub,   &&imul,   &&idiv, &&fadd,   &&fsub,   &&fmul,
                                     &&fdiv,  &&and_,  &&or_,    &&xor_,   &&eq,   &&ne,     &&lt,     &&le,
                                     &&gt,    &&ge,    &&feq,    &&fne,    &&flt,  &&fle,    &&fgt,    &&fge,
                                     &&iscan, &&fscan, &&iprint, &&fprint, &&sin,  &&cos,    &&pow,    &&load,
                                     &&move,  &&fload, &&fmove,  &&call,   &&ret,  &&newarr, &&strarr, &&ldarr};

    Instruction *cur_instr = new Instruction;
    *cur_instr = decoder_->Decode(FetchNext(code, pc));
    goto *dispatch_table[cur_instr->GetInstOpcode()];

#define NEXT()                                          \
    pc += 4;                                            \
    *cur_instr = decoder_->Decode(FetchNext(code, pc)); \
    goto *dispatch_table[cur_instr->GetInstOpcode()];

exit:
    Frame::DeleteLast();
    assert(Frame::GetFrames()->size() == 0);  // expecting all frames to be freed before exit
    delete cur_instr;
    return;
iadd:
    *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) =
        *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) + *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
isub:
    *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) =
        *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) - *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
imul:
    *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) =
        *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) * *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
idiv:
    try {
        auto right = *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2()));
        if (right == 0) {
            throw std::runtime_error("Division by zero error.");
        }
        *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) =
            static_cast<int64_t>(*ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) / right);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        std::abort();
    }
    NEXT();
fadd:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) +
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fsub:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) -
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fmul:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) *
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fdiv:
    try {
        auto right = *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
        if (std::fpclassify(right) == FP_ZERO) {
            throw std::runtime_error("Division by zero error.");
        }
        *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
            *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) / right;
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        std::abort();
    }
    NEXT();
and_:
    assert(false);  // Not implemented
    NEXT();
or_:
    assert(false);  // Not implemented
    NEXT();
xor_:
    assert(false);  // Not implemented
    NEXT();
eq:
    assert(false);  // Not implemented
    NEXT();
ne:
    assert(false);  // Not implemented
    NEXT();
lt:
    assert(false);  // Not implemented
    NEXT();
le:
    assert(false);  // Not implemented
    NEXT();
gt:
    assert(false);  // Not implemented
    NEXT();
ge:
    assert(false);  // Not implemented
    NEXT();
feq:
    assert(false);  // Not implemented
    NEXT();
fne:
    assert(false);  // Not implemented
    NEXT();
flt:
    assert(false);  // Not implemented
    NEXT();
fle:
    assert(false);  // Not implemented
    NEXT();
fgt:
    assert(false);  // Not implemented
    NEXT();
fge:
    assert(false);  // Not implemented
    NEXT();
iscan:
    scanf("%ld", ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)));
    NEXT();
fscan:
    scanf("%lf", ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)));
    NEXT();
iprint:
    printf("%ld\n", *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
fprint:
    printf("%lf\n", *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
sin:  // arguments are only put to float registers
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
        std::sin(*ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
cos:  // arguments are only put to float registers
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
        std::cos(*ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
pow:  // arguments are only put to float registers
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM)) =
        std::pow(*ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)),
                 *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2())));
    NEXT();
load:
    *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) = vm_file_->GetConst<VMReg>(cur_instr->imm);
    NEXT();
move:
    *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) = *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fload:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) = vm_file_->GetConst<VMFReg>(cur_instr->imm);
    NEXT();
fmove:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) = *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
call:
    int64_t jump_offset = vm_file_->GetConst<VMReg>(cur_instr->imm);
    size_t num_of_args = *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r));
    *ToNativePtr<VMReg>(frame->GetRegPtr(20)) = pc;  // saving pc to return
    void *prev_fr_mem = frame->GetRawMem();
    frame = Frame::CreateNew();
    frame->SetUpForCall(num_of_args, jump_offset, pc, prev_fr_mem);
    // changing pc
    pc = pc + jump_offset - 4;  // (-4) because NEXT() adds 4

    NEXT();
ret:
    VMFReg result = *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::ACCUM));
    frame = Frame::DeleteLast();
    assert(frame != nullptr);
    // restoring pc
    pc = *ToNativePtr<VMReg>(frame->GetRegPtr(20));
    // saving result to the current accum
    *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) = *ToNativePtr<VMReg>(&result);
    NEXT();
newarr:
    Types type = *ToNativePtr<Types>(frame->GetRegPtr(cur_instr->GetR2()));
    size_t size = Array::ComputeSize(*ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)), type);
    void *arr_ptr = Frame::GetCurrent()->GetFreeMemPtr(size);
    Array *arr = Array::CreateArray(arr_ptr, size, type);
    *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) = *ToNativePtr<VMReg>(arr);
    NEXT();
strarr:
    arr = ToNativePtr<Array>(frame->GetRegPtr(Registers::ACCUM));
    arr->SetValueByIdx(*ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)),
                       *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2())));
    NEXT();
ldarr:
    arr = ToNativePtr<Array>(frame->GetRegPtr(Registers::ACCUM));
    *ToNativePtr<VMReg>(frame->GetRegPtr(Registers::ACCUM)) =
        arr->GetValueByIdx(*ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
}

}  // namespace vm
