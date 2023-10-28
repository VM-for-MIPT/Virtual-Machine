import os
import sys
import yaml
from io import TextIOWrapper

class Instr:
    def __init__(self, name: str, descr: dict):
        self.name = name
        self.opcode = descr["opcode"]
        self.fields = descr["fields_shifts"]

def load_instrs(in_name: str) -> list:
    with open(in_name, 'r') as file:
        instrs = yaml.safe_load(file)

    return [Instr(instr_name, instr_descr) for instr_name, instr_descr in instrs.items()]

def gen_file_open(out: TextIOWrapper):
    out.write(
        "#ifndef INSTR_OPCODE_GEN_HPP\n"
        "#define INSTR_OPCODE_GEN_HPP\n\n"

        "#include \"types.hpp\"\n\n"

        "namespace vm {\n\n"

        "enum Opcode : uint8_t {\n"
    )

def gen_enum_value(out: TextIOWrapper, instr: Instr):
    out.write("%s = %d,\n" % (instr.name, instr.opcode))

def gen_instr_generator_function(out: TextIOWrapper, instr: Instr):
    out.write("VMInstr %sGen(" % (instr.name))
    if instr.fields:
        counter = 1
        length = len(instr.fields)
        for field in instr.fields:
            if counter == length:
                out.write("uint32_t %s" % (field))
            else:
                out.write("uint32_t %s, " % (field))
            counter += 1
    out.write(") {\n\n")
    out.write("VMInstr val = 0;\nval |= Opcode::%s;\n" % (instr.name))
    if instr.fields:
        for field, offset in instr.fields.items():
            if field.startswith("r"):
                # we know that r value is encoded by one byte
                out.write("val |= (%s << %d);\n" % (field, int(offset)))
            elif field == "imm":
                # assume that imm consists of 2 bytes to save (keep in mind: we have little endian)
                out.write("val |= (((%s >> 8) & (TwoPow<8>() - 1)) << %d);\n" % (field, int(offset)))
                out.write("val |= ((%s & (TwoPow<8>() - 1)) << %d);\n" % (field, int(offset) + 8))
            else:
                raise RuntimeError("Unknown field: %s" % (field))
    out.write("return val;\n}\n\n")


def gen_file_close(out: TextIOWrapper):
    out.write(
        "} // namespace vm\n\n"

        "#endif // INSTR_OPCODE_GEN_HPP\n"
    )

if __name__ == "__main__":
    IN_NAME = sys.argv[1]
    OUT_NAME = sys.argv[2]

    instrs = load_instrs(IN_NAME)

    if not os.path.exists(os.path.dirname(OUT_NAME)):
        os.makedirs(os.path.dirname(OUT_NAME))
    out = open(OUT_NAME, 'w')
    gen_file_open(out)

    for instr in instrs:
        gen_enum_value(out, instr)
    out.write("};\n\n")

    for instr in instrs:
        gen_instr_generator_function(out, instr)

    gen_file_close(out)
    out.close()
    os.system("clang-format -i %s" % OUT_NAME)