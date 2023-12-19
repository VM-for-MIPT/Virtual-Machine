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

TEST(InterpreterTest, DISABLED_CallTest)
{
    std::vector<VMInstr> byte_code;
    char *mem_for_consts = new char[4 + 4];
    *reinterpret_cast<int *>(mem_for_consts) = 2;
    *reinterpret_cast<int *>(mem_for_consts) = -28;  // change to offset
    std::vector<std::tuple<Types, size_t, void *>> const_pool;
    const_pool.push_back({Types::INT, 4, reinterpret_cast<int *>(mem_for_consts)});
    const_pool.push_back({Types::INT, 4, reinterpret_cast<int *>(mem_for_consts + 4)});

    byte_code.push_back(FADDGen(Registers::R1, Registers::R2));  // saved (a + b) to accum
    byte_code.push_back(RETGen());                               // return to the previous frame

    byte_code.push_back(FSCANGen());
    byte_code.push_back(FMOVEGen(Registers::R1, Registers::FACCUM));  // scanf of the first value (a) to D1
    byte_code.push_back(FSCANGen());
    byte_code.push_back(FMOVEGen(Registers::R2, Registers::FACCUM));  // scanf of the first value (a) to D2

    byte_code.push_back(vm::FLOADGen(Registers::ACCUM, 0));  // load to accum number of arguments (2 arguments)
    byte_code.push_back(CALLGen(Registers::ACCUM, 1));       // call func

    byte_code.push_back(vm::FPRINTGen(vm::Registers::ACCUM));  // printing sum value
    byte_code.push_back(vm::EXITGen());                        // return 0;

    VMFile *vm_file = new VMFile(reinterpret_cast<VMByte *>(byte_code.data()) + 8, const_pool);
    Interpreter *inter = Interpreter::CreateInterpreter(vm_file);
    inter->Run();
    Interpreter::Destroy(inter);
    delete[] mem_for_consts;
}

}  // namespace vm

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}