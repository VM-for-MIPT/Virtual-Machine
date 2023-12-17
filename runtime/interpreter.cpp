#include <iostream>
#include <cassert>
#include "interpreter.hpp"

namespace vm {
Interpreter::Interpreter(VMFile *vm_file) : vm_file_(vm_file)
{
    decoder_ = Decoder::CreateDecoder();
    executor_ = Executor::CreateExecutor();
}
Interpreter::~Interpreter()
{
    [[maybe_unused]] bool success = Decoder::Destroy(decoder_) & Executor::Destroy(executor_);
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
    static void *dispatch_table[] = {&&exit,   &&iadd, &&isub, &&imul, &&idiv, &&fadd, &&fsub,  &&fmul,  &&fdiv,
                                     &&and_,   &&or_,  &&xor_, &&eq,   &&ne,   &&lt,   &&le,    &&gt,    &&ge,
                                     &&feq,    &&fne,  &&flt,  &&fle,  &&fgt,  &&fge,  &&iscan, &&fscan, &&iprint,
                                     &&fprint, &&sin,  &&cos,  &&pow,  &&load, &&move, &&fload, &&fmove};
    auto &registers = executor_->GetRegisters();
    auto &fregisters = executor_->GetFRegisters();
    VMReg &pc = registers[20];
    Instruction *cur_instr = new Instruction;
    *cur_instr = decoder_->Decode(FetchNext(code, pc));
    goto *dispatch_table[cur_instr->GetInstOpcode()];

#define NEXT()                                          \
    pc += 4;                                            \
    *cur_instr = decoder_->Decode(FetchNext(code, pc)); \
    goto *dispatch_table[cur_instr->GetInstOpcode()];

exit:
    delete cur_instr;
    return;
iadd:
    registers[Registers::ACCUM] = registers[cur_instr->r] + registers[cur_instr->GetR2()];
    NEXT();
isub:
    registers[Registers::ACCUM] = registers[cur_instr->r] - registers[cur_instr->GetR2()];
    NEXT();
imul:
    registers[Registers::ACCUM] = registers[cur_instr->r] * registers[cur_instr->GetR2()];
    NEXT();
idiv:
    try {
        auto right = registers[cur_instr->GetR2()];
        if (right == 0) {
            throw std::runtime_error("Division by zero error.");
        }
        registers[Registers::ACCUM] = static_cast<int64_t>(registers[cur_instr->r] / right);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        std::abort();
    }
    NEXT();
fadd:
    fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] + fregisters[cur_instr->GetR2()];
    NEXT();
fsub:
    fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] - fregisters[cur_instr->GetR2()];
    NEXT();
fmul:
    fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] * fregisters[cur_instr->GetR2()];
    NEXT();
fdiv:
    try {
        auto right = fregisters[cur_instr->GetR2()];
        if (std::fpclassify(right) == FP_ZERO) {
            throw std::runtime_error("Division by zero error.");
        }
        fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] / right;
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
    scanf("%ld", &registers[Registers::ACCUM]);
    NEXT();
fscan:
    scanf("%lf", &fregisters[FRegisters::FACCUM]);
    NEXT();
iprint:
    printf("%ld\n", registers[cur_instr->r]);
    NEXT();
fprint:
    printf("%lf\n", fregisters[cur_instr->r]);
    NEXT();
sin:  // arguments are only put to float registers
    fregisters[FRegisters::FACCUM] = std::sin(fregisters[cur_instr->r]);
    NEXT();
cos:  // arguments are only put to float registers
    fregisters[FRegisters::FACCUM] = std::cos(fregisters[cur_instr->r]);
    NEXT();
pow:  // arguments are only put to float registers
    fregisters[FRegisters::FACCUM] = std::pow(fregisters[cur_instr->r], fregisters[cur_instr->GetR2()]);
    NEXT();
load:
    registers[cur_instr->r] = vm_file_->GetConst<int>(cur_instr->imm);
    NEXT();
move:
    registers[cur_instr->r] = registers[cur_instr->GetR2()];
    NEXT();
fload:
    fregisters[cur_instr->r] = vm_file_->GetConst<double>(cur_instr->imm);
    NEXT();
fmove:
    fregisters[cur_instr->r] = fregisters[cur_instr->GetR2()];
    NEXT();
}

}  // namespace vm