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
        &&iscan, &&fscan, &&iprint, &&fprint, &&sin, &&cos, &&pow
    };
    auto& registers = executor_->GetRegisters();
    auto& fregisters = executor_->GetFRegisters();
    VMReg& pc = registers[20];
    Instruction* cur_instr = new Instruction;
    *cur_instr = decoder_->Decode(FetchNext(code, pc));
    goto *dispatch_table[cur_instr->GetInstId()];

    #define NEXT() \
        pc += 4; \
        *cur_instr = decoder_->Decode(FetchNext(code, pc));\
        goto *dispatch_table[cur_instr->GetInstId()];

    exit:
        return;
    iadd:
        registers[Registers::ACCUM] = registers[cur_instr->r] + cur_instr->imm;
        NEXT();
    isub:
        registers[Registers::ACCUM] = registers[cur_instr->r] - cur_instr->imm;
        NEXT();
    imul:
        registers[Registers::ACCUM] = registers[cur_instr->r] * cur_instr->imm;
        NEXT();
    idiv:
        try {
            auto left = cur_instr->imm;
            if(left == 0) {
                throw std::runtime_error("Division by zero error.");
            }
            registers[Registers::ACCUM] = static_cast<int64_t>(registers[cur_instr->r] / left);
        }
        catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
        NEXT();
    fadd:
        fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] + cur_instr->imm;
        NEXT();
    fsub:
        fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] - cur_instr->imm;
        NEXT();
    fmul:
        fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] * cur_instr->imm;
        NEXT();
    fdiv:
        try{
            auto left = cur_instr->imm;
            if(std::fpclassify(left) == FP_ZERO) {
                throw std::runtime_error("Division by zero error.");
            }
            fregisters[FRegisters::FACCUM] = fregisters[cur_instr->r] / left;
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
        scanf("%ld", &registers[cur_instr->r]);
        NEXT();
    fscan:
        scanf("%lf", &fregisters[cur_instr->r]);
        NEXT();
    iprint:
        printf("%ld", registers[cur_instr->r]);
        NEXT();
    fprint:
        printf("%lf", fregisters[cur_instr->r]);
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
}

} // namespace vm 