#include <stdio.h>
#include <gtest/gtest.h>

#include "ThreadEndTest.hpp"
#include "ThreadQueue.hpp"
#include "ThreadEvent.hpp"

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}