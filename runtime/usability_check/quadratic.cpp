#include <vector>
#include "interpreter.hpp"
#include "instr_opcode.gen.hpp"

int main()
{
    std::vector<vm::VMInstr> byte_code;
    // double constants[] = {2, 4, 0.5, 0};
    char *mem_for_consts = new char[8 + 8 + 8 + 8];
    // This should be moved to VMFile
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
    byte_code.push_back(vm::FMOVEGen(1, 0));  // scanf of the  first value (a) to r1

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(2, 0));  // scanf of the second value (b) to r2

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(3, 0));  // scanf of the  third value (c) to r3

    byte_code.push_back(vm::FLOADGen(0, 0));  // saved 2 to faccum
    byte_code.push_back(vm::POWGen(2, 0));    // saved (b^2) to faccum
    byte_code.push_back(vm::FMOVEGen(5, 0));  // moved (b^2) from faccum to r5

    byte_code.push_back(vm::FMULGen(1, 3));   // saved (a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved (a * c) from faccum to r4

    byte_code.push_back(vm::FLOADGen(6, 1));  // saved 4U to r6

    byte_code.push_back(vm::FMULGen(4, 6));   // saved (4 * a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved (4 * a * c) from faccum to r4

    byte_code.push_back(vm::FSUBGen(5, 4));   // saved (b^2 - 4 * a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved (b^2 - 4 * a * c) to r4

    byte_code.push_back(vm::FLOADGen(0, 2));  // saved 0.5 to faccum
    byte_code.push_back(vm::POWGen(4, 0));    // saved sq_D = sqrt(b^2 - 4 * a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved sq_D to r4

    byte_code.push_back(vm::FLOADGen(0, 3));  // saved 0U to faccum
    byte_code.push_back(vm::FSUBGen(0, 2));   // saved (-b) to faccum
    byte_code.push_back(vm::FMOVEGen(5, 0));  // moved (-b) from faccum to r5

    byte_code.push_back(vm::FSUBGen(5, 4));   // saved (-b - sq_D) to faccum
    byte_code.push_back(vm::FMOVEGen(6, 0));  // moved (-b - sq_D) to r6
    byte_code.push_back(vm::FLOADGen(0, 0));  // saved 2U to faccum
    byte_code.push_back(vm::FDIVGen(6, 0));   // saved (-b - sq_D) / 2 to faccum
    byte_code.push_back(vm::FDIVGen(0, 1));   // saved (-b - sq_D) / 2a to faccum
    byte_code.push_back(vm::FPRINTGen(0));    // print(x1 = (-b - sq_D) / 2a)

    byte_code.push_back(vm::FADDGen(5, 4));   // saved (-b + sq_D) to faccum
    byte_code.push_back(vm::FMOVEGen(6, 0));  // moved (-b + sq_D) to r6
    byte_code.push_back(vm::FLOADGen(0, 0));  // saved 2U to faccum
    byte_code.push_back(vm::FDIVGen(6, 0));   // saved (-b + sq_D) / 2 to faccum
    byte_code.push_back(vm::FDIVGen(0, 1));   // saved (-b + sq_D) / 2a to faccum
    byte_code.push_back(vm::FPRINTGen(0));    // print(x2 = (-b + sq_D) / 2a)

    byte_code.push_back(vm::EXITGen());  // return 0;

    vm::VMFile *vm_file = new vm::VMFile(reinterpret_cast<vm::VMByte *>(byte_code.data()), const_pool);
    vm::Interpreter *inter = vm::Interpreter::CreateInterpreter(vm_file);
    inter->Run();
    vm::Interpreter::Destroy(inter);
    delete[] mem_for_consts;

    return 0;
}
