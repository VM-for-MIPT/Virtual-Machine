#include <gtest/gtest.h>
#include "interpreter.hpp"

namespace vm {
TEST(InterpreterTest, InterpreterTestInitial) {
    Interpreter* inter = Interpreter::CreateInterpreter();
    ASSERT_TRUE(Interpreter::Destroy(inter));
}

} // namespace vm

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}