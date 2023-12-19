#include <vector>
#include "interpreter.hpp"
#include "instr_opcode.gen.hpp"
#include "registers.hpp"

int main()
{
    std::vector<vm::VMInstr> byte_code;
    char *mem_for_consts = new char[8 + 8 + 8 + 8];

    *reinterpret_cast<double *>(mem_for_consts) = 2.0;
    *reinterpret_cast<double *>(mem_for_consts + 8) = 4.0;
    *reinterpret_cast<double *>(mem_for_consts + 16) = 0.5;
    *reinterpret_cast<double *>(mem_for_consts + 24) = 0.0;

    std::vector<std::tuple<vm::Types, size_t, void *>> const_pool;
    const_pool.push_back({vm::Types::DOUBLE, 8, reinterpret_cast<int *>(mem_for_consts)});
    const_pool.push_back({vm::Types::DOUBLE, 8, reinterpret_cast<int *>(mem_for_consts + 8)});
    const_pool.push_back({vm::Types::DOUBLE, 8, reinterpret_cast<int *>(mem_for_consts + 16)});
    const_pool.push_back({vm::Types::DOUBLE, 8, reinterpret_cast<int *>(mem_for_consts + 24)});

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D1, vm::Registers::ACCUM));  // scanf of the  first value (a) to D1

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D2, vm::Registers::ACCUM));  // scanf of the second value (b) to D2

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D3, vm::Registers::ACCUM));  // scanf of the  third value (c) to D3

    byte_code.push_back(vm::FLOADGen(vm::Registers::ACCUM, 0));                  // saved 2 to accum
    byte_code.push_back(vm::POWGen(vm::Registers::D2, vm::Registers::ACCUM));    // saved (b^2) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D5, vm::Registers::ACCUM));  // moved (b^2) from accum to D5

    byte_code.push_back(vm::FMULGen(vm::Registers::D1, vm::Registers::D3));      // saved (a * c) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D4, vm::Registers::ACCUM));  // moved (a * c) from accum to D4

    byte_code.push_back(vm::FLOADGen(vm::Registers::D6, 1));  // saved 4U to D6

    byte_code.push_back(vm::FMULGen(vm::Registers::D4, vm::Registers::D6));      // saved (4 * a * c) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D4, vm::Registers::ACCUM));  // moved (4 * a * c) from accum to D4

    byte_code.push_back(vm::FSUBGen(vm::Registers::D5, vm::Registers::D4));      // saved (b^2 - 4 * a * c) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D4, vm::Registers::ACCUM));  // moved (b^2 - 4 * a * c) to D4

    byte_code.push_back(vm::FLOADGen(vm::Registers::ACCUM, 2));  // saved 0.5 to accum
    byte_code.push_back(
        vm::POWGen(vm::Registers::D4, vm::Registers::ACCUM));  // saved sq_D = sqrt(b^2 - 4 * a * c) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D4, vm::Registers::ACCUM));  // moved sq_D to D4

    byte_code.push_back(vm::FLOADGen(vm::Registers::ACCUM, 3));                  // saved 0U to accum
    byte_code.push_back(vm::FSUBGen(vm::Registers::ACCUM, vm::Registers::D2));   // saved (-b) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D5, vm::Registers::ACCUM));  // moved (-b) from accum to D5

    byte_code.push_back(vm::FSUBGen(vm::Registers::D5, vm::Registers::D4));      // saved (-b - sq_D) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D6, vm::Registers::ACCUM));  // moved (-b - sq_D) to D6
    byte_code.push_back(vm::FLOADGen(vm::Registers::ACCUM, 0));                  // saved 2U to accum
    byte_code.push_back(vm::FDIVGen(vm::Registers::D6, vm::Registers::ACCUM));   // saved (-b - sq_D) / 2 to accum
    byte_code.push_back(vm::FDIVGen(vm::Registers::ACCUM, vm::Registers::D1));   // saved (-b - sq_D) / 2a to accum
    byte_code.push_back(vm::FPRINTGen(vm::Registers::ACCUM));                    // print(x1 = (-b - sq_D) / 2a)

    byte_code.push_back(vm::FADDGen(vm::Registers::D5, vm::Registers::D4));      // saved (-b + sq_D) to accum
    byte_code.push_back(vm::FMOVEGen(vm::Registers::D6, vm::Registers::ACCUM));  // moved (-b + sq_D) to D6
    byte_code.push_back(vm::FLOADGen(vm::Registers::ACCUM, 0));                  // saved 2U to accum
    byte_code.push_back(vm::FDIVGen(vm::Registers::D6, vm::Registers::ACCUM));   // saved (-b + sq_D) / 2 to accum
    byte_code.push_back(vm::FDIVGen(vm::Registers::ACCUM, vm::Registers::D1));   // saved (-b + sq_D) / 2a to accum
    byte_code.push_back(vm::FPRINTGen(vm::Registers::ACCUM));                    // print(x2 = (-b + sq_D) / 2a)

    byte_code.push_back(vm::EXITGen());  // return 0;

    vm::VMFile *vm_file = new vm::VMFile(reinterpret_cast<vm::VMByte *>(byte_code.data()), const_pool);
    vm::Interpreter *inter = vm::Interpreter::CreateInterpreter(vm_file);
    inter->Run(0);
    vm::Interpreter::Destroy(inter);
    delete[] mem_for_consts;

    return 0;
}
