#include <iostream>
#include <cassert>
#include "interpreter.hpp"
#include "frame.hpp"
#include "registers.hpp"

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

void Interpreter::Run()
{
    VMByte *code = vm_file_->GetCode();
    assert(Frame::GetFrames()->size() == 0);
    Frame::CreateNew();
    auto frame = Frame::GetCurrent();
    assert(frame != nullptr);
    assert(Frame::GetFrames()->size() != 0);
    VMReg *pc = ToNativePtr<VMReg>(frame->GetRegPtr(20));
    static void *dispatch_table[] = {&&exit,   &&iadd, &&isub, &&imul, &&idiv, &&fadd, &&fsub,  &&fmul,  &&fdiv,
                                     &&and_,   &&or_,  &&xor_, &&eq,   &&ne,   &&lt,   &&le,    &&gt,    &&ge,
                                     &&feq,    &&fne,  &&flt,  &&fle,  &&fgt,  &&fge,  &&iscan, &&fscan, &&iprint,
                                     &&fprint, &&sin,  &&cos,  &&pow,  &&load, &&move, &&fload, &&fmove};

    Instruction *cur_instr = new Instruction;
    *cur_instr = decoder_->Decode(FetchNext(code, *pc));
    goto *dispatch_table[cur_instr->GetInstOpcode()];

#define NEXT()                                           \
    *pc += 4;                                            \
    *cur_instr = decoder_->Decode(FetchNext(code, *pc)); \
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
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) +
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fsub:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) -
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fmul:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) *
        *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fdiv:
    try {
        auto right = *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
        if (std::fpclassify(right) == FP_ZERO) {
            throw std::runtime_error("Division by zero error.");
        }
        *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
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
    scanf("%lf", ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)));
    NEXT();
iprint:
    printf("%ld\n", *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
fprint:
    printf("%lf\n", *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
sin:  // arguments are only put to float registers
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
        std::sin(*ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
cos:  // arguments are only put to float registers
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
        std::cos(*ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)));
    NEXT();
pow:  // arguments are only put to float registers
    *ToNativePtr<VMFReg>(frame->GetRegPtr(Registers::FACCUM)) =
        std::pow(*ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)),
                 *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2())));
    NEXT();
load:
    *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) = vm_file_->GetConst<int>(cur_instr->imm);
    NEXT();
move:
    *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->r)) = *ToNativePtr<VMReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
fload:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) = vm_file_->GetConst<double>(cur_instr->imm);
    NEXT();
fmove:
    *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->r)) = *ToNativePtr<VMFReg>(frame->GetRegPtr(cur_instr->GetR2()));
    NEXT();
}

}  // namespace vm