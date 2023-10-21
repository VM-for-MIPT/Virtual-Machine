#include <cassert>

#include "instruction.hpp"
#include "types.hpp"

// TODO: autogenerate this

namespace vm {
VMInstr EXITGen()
{
    return 0;
}

VMInstr IADDGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::IADD;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr ISUBGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::ISUB;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr IMULGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::IMUL;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr IDIVGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::IDIV;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr FADDGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::FADD;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr FSUBGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::FSUB;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr FMULGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::FMUL;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr FDIVGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::FDIV;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr ANDGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::AND;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr ORGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::OR;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr XORGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::XOR;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr EQGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::EQ;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr NEGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::NE;
    val |= (reg_id << 8);
    val |= (imm << 16);
    return val;
}

VMInstr LTGen()
{
    // to be implemented
    return 0;
}

VMInstr LEGen()
{
    // to be implemented
    return 0;
}

VMInstr GTGen()
{
    // to be implemented
    return 0;
}

VMInstr GEGen()
{
    // to be implemented
    return 0;
}

VMInstr FEQGen()
{
    // to be implemented
    return 0;
}

VMInstr FNEGen()
{
    // to be implemented
    return 0;
}

VMInstr FLTGen()
{
    // to be implemented
    return 0;
}

VMInstr FLEGen()
{
    // to be implemented
    return 0;
}

VMInstr FGTGen()
{
    // to be implemented
    return 0;
}

VMInstr FGEGen()
{
    // to be implemented
    return 0;
}

VMInstr ISCANGen()
{
    VMInstr val = 0;
    val |= Opcode::ISCAN;
    return val;
}

VMInstr FSCANGen()
{
    VMInstr val = 0;
    val |= Opcode::FSCAN;
    return val;
}

VMInstr IPRINTGen(uint32_t reg_id)
{
    VMInstr val = 0;
    val |= Opcode::IPRINT;
    val |= (reg_id << 8);
    return val;
}

VMInstr FPRINTGen(uint32_t reg_id)
{
    VMInstr val = 0;
    val |= Opcode::FPRINT;
    val |= (reg_id << 8);
    return val;
}

VMInstr SINGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::SIN;
    val |= (reg_id << 8);
    val |= ((imm >> 8) & (TwoPow<8>() - 1)) << 16;
    val |= (imm & (TwoPow<8>() - 1)) << 24;
    return val;
}

VMInstr COSGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::COS;
    val |= (reg_id << 8);
    val |= ((imm >> 8) & (TwoPow<8>() - 1)) << 16;
    val |= (imm & (TwoPow<8>() - 1)) << 24;
    return val;
}

VMInstr POWGen(uint32_t reg_id, uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::POW;
    val |= (reg_id << 8);
    val |= ((imm >> 8) & (TwoPow<8>() - 1)) << 16;
    val |= (imm & (TwoPow<8>() - 1)) << 24;
    return val;
}

VMInstr SQRTGen(uint32_t reg_id)
{
    VMInstr val = 0;
    val |= Opcode::SQRT;
    val |= (reg_id << 8);
    return val;
}

VMInstr LOADGen(uint32_t imm)
{
    VMInstr val = 0;
    val |= Opcode::LOAD;
    val |= ((imm >> 8) & (TwoPow<8>() - 1)) << 16;
    val |= (imm & (TwoPow<8>() - 1)) << 24;
    return val;
}

VMInstr MOVEGen(uint32_t reg1_id, uint32_t reg2_id)
{
    VMInstr val = 0;
    val |= Opcode::MOVE;
    val |= (reg1_id << 8);
    val |= (reg2_id << 16);
    return val;
}

VMInstr FLOADGen(uint32_t imm)
{
    assert(imm < TwoPow<16>());
    VMInstr val = 0;
    val |= Opcode::FLOAD;
    val |= ((imm >> 8) & (TwoPow<8>() - 1)) << 16;
    val |= (imm & (TwoPow<8>() - 1)) << 24;
    return val;
}

VMInstr FMOVEGen(uint32_t reg1_id, uint32_t reg2_id)
{
    VMInstr val = 0;
    val |= Opcode::FMOVE;
    val |= (reg1_id << 8);
    val |= (reg2_id << 16);
    return val;
}
}  // namespace vm