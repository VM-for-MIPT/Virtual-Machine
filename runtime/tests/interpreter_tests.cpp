#include <gtest/gtest.h>
#include "interpreter.hpp"

namespace vm {
TEST(InterpreterTest, InterpreterTestInitial) {
    Interpreter* intrprtr = Interpreter::CreateInterpreter();
    ASSERT_TRUE(Interpreter::Destroy(intrprtr));
}

} // namespace vm

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}