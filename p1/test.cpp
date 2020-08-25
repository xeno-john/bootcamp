#include<gtest/gtest.h>
#include<iostream>
#include "p1.h"

TEST(PrintBits,PrecisionTest)
{
    /* negative input is not possible because it is verified in the 
     * main function of the program
     * -> not relevant to test
     * and bigger numbers than 4294967295 are not allowed in C++
     */
    ASSERT_STREQ("00000000000000000000000000000011",print_bits(3));
    ASSERT_STREQ("00000000000000000000000000000010",print_bits(2));
    ASSERT_STREQ("00000000000000000000000000000000",print_bits(0));
    ASSERT_STREQ("00000000000000000000000001000000",print_bits(64));
    ASSERT_STREQ("11111111111111111111111111111111",print_bits(4294967295));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}