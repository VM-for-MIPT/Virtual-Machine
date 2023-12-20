#include <gtest/gtest.h>
#include "interpreter.hpp"
#include "instr_opcode.gen.hpp"
#include "registers.hpp"

namespace vm {
TEST(InterpreterTest, InterpreterTestInitial)
{
    Interpreter *inter = Interpreter::CreateInterpreter(nullptr);
    ASSERT_TRUE(Interpreter::Destroy(inter));
}

TEST(InterpreterTest, CallTest)
{
    std::vector<VMInstr> byte_code;
    char *mem_for_consts = new char[8 + 8];
    *reinterpret_cast<int64_t *>(mem_for_consts) = 2;
    *reinterpret_cast<int64_t *>(mem_for_consts + 8) = -24;  // change to offset
    std::vector<std::tuple<Types, size_t, void *>> const_pool;
    const_pool.push_back({Types::INT, 8, reinterpret_cast<void *>(mem_for_consts)});
    const_pool.push_back({Types::INT, 8, reinterpret_cast<void *>(mem_for_consts + 8)});

    byte_code.push_back(FADDGen(Registers::ACCUM, Registers::R1));  // saved (a + b) to accum
    byte_code.push_back(RETGen());                                  // return to the previous frame

    byte_code.push_back(FSCANGen());
    byte_code.push_back(FMOVEGen(Registers::R1, Registers::ACCUM));  // scanf of the first value (a) to R1
    byte_code.push_back(FSCANGen());
    // byte_code.push_back(FMOVEGen(Registers::R2, Registers::ACCUM));  // scanf of the first value (a) to R2

    byte_code.push_back(LOADGen(Registers::R2, 0));  // load to R2 number of arguments (2 arguments)
    byte_code.push_back(CALLGen(Registers::R2, 1));  // call func

    byte_code.push_back(FPRINTGen(Registers::ACCUM));  // printing sum value
    byte_code.push_back(EXITGen());                    // return 0;

    VMFile *vm_file = new VMFile(reinterpret_cast<VMByte *>(byte_code.data()), const_pool);
    Interpreter *inter = Interpreter::CreateInterpreter(vm_file);
    inter->Run(8);
    Interpreter::Destroy(inter);
    delete[] mem_for_consts;
}

TEST(InterpreterTest, ArrTest)
{
    std::vector<VMInstr> byte_code;
    std::vector<std::tuple<Types, size_t, void *>> const_pool;
    char *mem_for_consts = new char[8];
    *reinterpret_cast<int64_t *>(mem_for_consts) = 0;
    const_pool.push_back({Types::INT, 8, reinterpret_cast<void *>(mem_for_consts)});

    byte_code.push_back(FSCANGen());
    byte_code.push_back(FMOVEGen(Registers::R1, Registers::ACCUM));  // scanf of the arr length to R1
    byte_code.push_back(FSCANGen());
    byte_code.push_back(FMOVEGen(Registers::R2, Registers::ACCUM));  // scanf of the arr ind to store value to R2
    byte_code.push_back(FSCANGen());
    byte_code.push_back(FMOVEGen(Registers::R3, Registers::ACCUM));  // scanf of the arr val to store value to R3
    byte_code.push_back(
        NEWARRGen(Registers::R1, 0));  // creating array of length R1 and type 0 (INT) (array pointer saved in accum)
    byte_code.push_back(STRARRGen(Registers::R2, Registers::R3));  // storing value to array
    byte_code.push_back(LDARRGen(Registers::R2));                  // loading value from array
    byte_code.push_back(FPRINTGen(vm::Registers::ACCUM));          // printing sum value
    byte_code.push_back(EXITGen());                                // return 0;

    VMFile *vm_file = new VMFile(reinterpret_cast<VMByte *>(byte_code.data()), const_pool);
    Interpreter *inter = Interpreter::CreateInterpreter(vm_file);
    inter->Run(40);
    Interpreter::Destroy(inter);
    delete[] mem_for_consts;
}

}  // namespace vm

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}