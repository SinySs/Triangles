#include <iostream>
#include <cassert>

#include "triangle.h"

using namespace geometry;

int main(int argc, char **argv)
{
    int n;

    std::cin >> n;
    assert(std::cin.good());

    std::vector<point_t> points;
    std::vector<triangle_t> triangles;

    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            float x = NAN, y = NAN, z = NAN;
            std::cin >> x >> y >> z;
            assert(std::cin.good());

            points.push_back(point_t(x, y, z));
        }

        triangles.push_back(triangle_t(points[0], points[1], points[2]));
        points.clear();

    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++){
            if(intersect(triangles[i], triangles[j]))
                std::cout << i << ' ' << j << std::endl;
        }
    }*/

    for(int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            float x = NAN, y = NAN, z = NAN;
            std::cin >> x >> y >> z;
            assert(std::cin.good());

            points.push_back(point_t(x, y, z));
        }

    }

    plane_t p1(points[0], points[1], points[2]);
    plane_t p2(points[3], points[4], points[5]);

    vector_t v1 = p1.get_normal();
    vector_t v2 = p2.get_normal();

    v1.print();
    v2.print();
    line_t LINE(p1, p2);
    LINE.print();


    return 0;
}


