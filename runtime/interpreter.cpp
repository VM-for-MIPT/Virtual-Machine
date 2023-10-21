#include <cassert>
#include "interpreter.hpp"

namespace vm {
Interpreter::Interpreter() {
    decoder_ = Decoder::CreateDecoder();
    executor_ = Executor::CreateExecutor();
}
Interpreter::~Interpreter() {
    bool success = Decoder::Destroy(decoder_);
    success &= Executor::Destroy(executor_);
    assert(success);
}

/* static */
Interpreter *Interpreter::CreateInterpreter() {
    return new Interpreter;
}

/* static */
bool Interpreter::Destroy(Interpreter *interpreter) {
    assert(interpreter != nullptr);
    delete interpreter;
    return true;
}

VMInstr Interpreter::FetchNext(VMByte* code, VMReg pc) {
    return *reinterpret_cast<VMInstr *>(&code[pc]);
}

void Interpreter::Run(VMByte* code) {
    static void *dispatch_table[] = {
        &&exit, &&iadd, &&isub, &&imul, &&idiv, &&fadd, &&fsub, &&fmul, &&fdiv, &&and_, &&or_,
        &&xor_, &&eq, &&ne, &&lt, &&le, &&gt, &&ge, &&feq, &&fne, &&flt, &&fle, &&fgt, &&fge,
        &&iscan, &&fscan, &&iprint, &&fprint, &&sin, &&cos, &&pow, &&sqrt, &&load, &&move,
        &&fload, &&fmove
    };
    auto& registers = executor_->GetRegisters();
    auto& fregisters = executor_->GetFRegisters();
    VMReg& pc = registers[20];
    Instruction* cur_instr = new Instruction;
    *cur_instr = decoder_->Decode(FetchNext(code, pc));
    goto *dispatch_table[cur_instr->GetInstOpcode()];

    #define NEXT() \
        pc += 4; \
        *cur_instr = decoder_->Decode(FetchNext(code, pc));\
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
            if(right == 0) {
                throw std::runtime_error("Division by zero error.");
            }
            registers[Registers::ACCUM] = static_cast<int64_t>(registers[cur_instr->r] / right);
        }
        catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
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
        try{
            auto right = fregisters[cur_instr->GetR2()];
            if(std::fpclassify(right) == FP_ZERO) {
                throw std::runtime_error("Division by zero error.");
            }
            fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] / right;
        }
        catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
        NEXT();
    and_:
        
        NEXT();
    or_:
        
        NEXT();
    xor_:
        
        NEXT();
    eq:
        
        NEXT();
    ne:
        
        NEXT();
    lt:
        
        NEXT();
    le:
        
        NEXT();
    gt:
        
        NEXT();
    ge:
        
        NEXT();
    feq:
        
        NEXT();
    fne:
        
        NEXT();
    flt:
        
        NEXT();
    fle:
        
        NEXT();
    fgt:
        
        NEXT();
    fge:
        
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
    sin: // arguments are only put to float registers
        fregisters[FRegisters::FACCUM] = std::sin(fregisters[cur_instr->r]);
        NEXT();
    cos: // arguments are only put to float registers
        fregisters[FRegisters::FACCUM] = std::cos(fregisters[cur_instr->r]);        
        NEXT();
    pow: // arguments are only put to float registers
        fregisters[FRegisters::FACCUM] = std::pow(fregisters[cur_instr->r], cur_instr->imm);
        NEXT();
    sqrt: // arguments are only put to float registers
        fregisters[FRegisters::FACCUM] = std::sqrt(fregisters[cur_instr->r]);
        NEXT();
    load:
        registers[Registers::ACCUM] = cur_instr->imm;
        NEXT();
    move:
        registers[cur_instr->r] = registers[cur_instr->GetR2()];
        NEXT();
    fload:
        fregisters[FRegisters::FACCUM] = cur_instr->imm;
        NEXT();
    fmove:
        fregisters[cur_instr->r] = fregisters[cur_instr->GetR2()];
        NEXT();
}

} // namespace vm 