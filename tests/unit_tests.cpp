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

TEST(Triangles, point_to_plane1) {
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

TEST(Triangles, point_to_plane2) {
    point_t p1(3, 3, 0);
    point_t p2(0, -3, 0);
    point_t p3(-1, 0, 1);

    plane_t pl(p1, p2, p3);

    point_t p(5, -3, 10);

    float dist = -10.95445;
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

TEST(Triangles, triangle_intersection1) {
    point_t p1(1, 1, 1);
    point_t p2(2, 0, 1);
    point_t p3(-1, -2, 0);

    point_t p4(-1, 2, 5);
    point_t p5(2, 4, 2);
    point_t p6(1, -2, 0);

    triangle_t t0(p1, p2, p3);
    triangle_t t1(p4, p5, p6);

    ASSERT_TRUE(intersect(t0, t1));
}

TEST(Triangles, triangle_intersection2) {
    point_t p1(0, 0, 0);
    point_t p2(0, 1, 0);
    point_t p3(1, 0, 0);

    point_t p4(0, 0, 0.6);
    point_t p5(1, 1, -0.4);
    point_t p6(1, 1, 0.6);

    triangle_t t0(p1, p2, p3);
    triangle_t t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

TEST(Triangles, triangle_intersection3) {
    point_t p1(0, 0, 0);
    point_t p2(0, 1, 0);
    point_t p3(1, 0, 0);

    point_t p4(0, 0, 1);
    point_t p5(0, 1, 1);
    point_t p6(1, 0, 1);

    triangle_t t0(p1, p2, p3);
    triangle_t t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

TEST(Triangles, triangle_intersection4) {
    point_t p1(0, 0, 0);
    point_t p2(0, 1, 0);
    point_t p3(1, 0, 1);

    point_t p4(0, 0, 0);
    point_t p5(0, 1, 0);
    point_t p6(-1, 0, 1);

    triangle_t t0(p1, p2, p3);
    triangle_t t1(p4, p5, p6);

    ASSERT_TRUE(intersect(t0, t1));
}

TEST(Triangles, triangle_intersection1_2D) {
    point_t p1(1, 0, 0);
    point_t p2(0, 0, 0);
    point_t p3(0, 1, 0);

    point_t p4(0, 0, 0);
    point_t p5(2, 2, 0);
    point_t p6(2, -2, 0);

    triangle_t t0(p1, p2, p3);
    triangle_t t1(p4, p5, p6);

    ASSERT_TRUE(intersect(t0, t1));
}

int main(int argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}