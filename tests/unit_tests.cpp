#include <gtest/gtest.h>
#include <iostream>
#include "../include/triangle.h"

using namespace geometry;


TEST(Triangles, points_equal)
{
    point_t p1(1, 0, 0);
    point_t p2(1, 0, 0);

    ASSERT_EQ(p1, p2);
}

TEST(Triangles, PointPlaneDistance) {
    point_t p1(1, 1, 1);
    point_t p2(2, 0, 1);
    point_t p3(-1, -2, 0);

    plane_t pl(p1, p2, p3);

    point_t p(6, 10, -23);

    float dist = 25.7883;
    float computed_dist = compute_distanse(p, pl);

    float precision = 1e-4;
    ASSERT_TRUE(std::abs(dist - computed_dist) < precision);
}
TEST(Triangles, vector_product) {

    point_t p1(2, 1, -2);
    point_t p2(4, -1, 1);
    point_t p3(0, -2, -1);

    vector_t v1(p2, p1);
    vector_t v2(p3, p1);

    vector_t norm = vector_product(v1, v2);
    vector_t res(7, -8, -10);
    ASSERT_EQ(norm, res);
}

TEST(Triangles, dot_product) {

    point_t p1(2, 1, -2);
    point_t p2(4, -1, 1);
    point_t p3(0, -2, -1);

    vector_t v1(p1, p2);
    vector_t v2(p1, p3);

    float dot = dot_product(v1, v2);
    ASSERT_EQ(dot, 5);
}

int main(int argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}