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
        &&iscan, &&fscan, &&iprint, &&fprint, &&sin, &&cos
    };
    auto& registers = executor_->GetRegisters();
    auto& fregisters = executor_->GetFRegisters();
    VMReg& pc = registers[20];
    Instruction* cur_instr = new Instruction;

    #define NEXT() \
        pc += 4; \
        *cur_instr = decoder_->Decode(FetchNext(code, pc));\
        goto *dispatch_table[cur_instr->GetInstId()];

    exit:

        NEXT();
    iadd:
        
        NEXT();
    isub:
        
        NEXT();
    imul:
        
        NEXT();
    idiv:
        
        NEXT();
    fadd:
        
        NEXT();
    fsub:
        
        NEXT();
    fmul:
        
        NEXT();
    fdiv:
        
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
        
        NEXT();
    fscan:
        
        NEXT();
    iprint:
        
        NEXT();
    fprint:
        
        NEXT();
    sin:
        
        NEXT();
    cos:
        
        NEXT();
}

} // namespace vm 