#include "pch.h"
#include "../Cpp-Multithreading-Playground/Semaphore_Binary.h"

class SemaphoreBinaryBasicTest : public ::testing::Test
{
protected:
    Semaphore_Binary s;

    SemaphoreBinaryBasicTest() : s{}
    {}
};

TEST_F(SemaphoreBinaryBasicTest, BasicUpDown) {
    s.down();
    s.up();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}