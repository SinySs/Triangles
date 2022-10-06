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

    triangle_t t1(points[0], points[1], points[2]);

    plane_t pl(t1);
    pl.print();

    triangle_t proj = project_to_XY(t1);
    std::vector<point_t> p = proj.get_points();
    for(int i = 0; i < 3; i++)
        p[i].print();


    return 0;
}


