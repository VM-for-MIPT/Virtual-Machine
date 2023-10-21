#include <vector>

#include "interpreter.hpp"
#include "inst_creator_inl.hpp"

int main()
{
    vm::Interpreter *inter = vm::Interpreter::CreateInterpreter();
    std::vector<vm::VMInstr> byte_code;

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(1, 0));  // scanf of the  first value (a) to r1

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(2, 0));  // scanf of the second value (b) to r2

    byte_code.push_back(vm::FSCANGen());
    byte_code.push_back(vm::FMOVEGen(3, 0));  // scanf of the  third value (c) to r3

    byte_code.push_back(vm::POWGen(2,
                                   reinterpret_cast<uint32_t>(2U)));  // saved (b^2) to faccum
    byte_code.push_back(vm::FMOVEGen(5, 0));                          // moved (b^2) from faccum to r5

    byte_code.push_back(vm::FMULGen(1, 3));   // saved (a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved (a * c) from faccum to r4

    byte_code.push_back(vm::FLOADGen(reinterpret_cast<uint32_t>(4U)));  // saved 4U to faccum
    byte_code.push_back(vm::FMOVEGen(6, 0));                            // saved 4U to r6

    byte_code.push_back(vm::FMULGen(4, 6));   // saved (4 * a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved (4 * a * c) from faccum to r4

    byte_code.push_back(vm::FSUBGen(5, 4));   // saved (b^2 - 4 * a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved (b^2 - 4 * a * c) to r4

    byte_code.push_back(vm::SQRTGen(4));      // saved sq_D = sqrt(b^2 - 4 * a * c) to faccum
    byte_code.push_back(vm::FMOVEGen(4, 0));  // moved sq_D to r4

    byte_code.push_back(vm::FLOADGen(reinterpret_cast<uint32_t>(0U)));  // saved 0U to faccum
    byte_code.push_back(vm::FSUBGen(0, 2));                             // saved (-b) to faccum
    byte_code.push_back(vm::FMOVEGen(5, 0));                            // moved (-b) from faccum to r5

    byte_code.push_back(vm::FSUBGen(5, 4));                             // saved (-b - sq_D) to faccum
    byte_code.push_back(vm::FMOVEGen(6, 0));                            // moved (-b - sq_D) to r6
    byte_code.push_back(vm::FLOADGen(reinterpret_cast<uint32_t>(2U)));  // saved 2U to faccum
    byte_code.push_back(vm::FDIVGen(6, 0));                             // saved (-b - sq_D) / 2 to faccum
    byte_code.push_back(vm::FDIVGen(0, 1));                             // saved (-b - sq_D) / 2a to faccum
    byte_code.push_back(vm::FPRINTGen(0));                              // print(x1 = (-b - sq_D) / 2a)

    byte_code.push_back(vm::FADDGen(5, 4));                             // saved (-b + sq_D) to faccum
    byte_code.push_back(vm::FMOVEGen(6, 0));                            // moved (-b + sq_D) to r6
    byte_code.push_back(vm::FLOADGen(reinterpret_cast<uint32_t>(2U)));  // saved 2U to faccum
    byte_code.push_back(vm::FDIVGen(6, 0));                             // saved (-b + sq_D) / 2 to faccum
    byte_code.push_back(vm::FDIVGen(0, 1));                             // saved (-b + sq_D) / 2a to faccum
    byte_code.push_back(vm::FPRINTGen(0));                              // print(x2 = (-b + sq_D) / 2a)

    byte_code.push_back(vm::EXITGen());  // return 0;

    inter->Run(reinterpret_cast<vm::VMByte *>(byte_code.data()));
    vm::Interpreter::Destroy(inter);

    return 0;
}
