#include <gtest/gtest.h>
#include <iostream>
#include "../include/triangle.h"


TEST(Triangles, Points_equal)
{
    point_t p1(1, 0, 0);
    point_t p2(1, 0, 0);

    ASSERT_EQ(p1, p2);
}

int main(int argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}