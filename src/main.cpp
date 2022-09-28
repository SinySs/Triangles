#include <iostream>
#include <cassert>

#include "triangle.h"

using namespace geometry;

int main(int argc, char **argv)
{
    int n;

    std::cin >> n;
    assert(std::cin.good());

    for(int i = 0; i < n; i++)
        {
            float x, y, z;

            std::cin >> x >> y >> z;
            assert(std::cin.good());
            point_t A1{x, y, z};
            A1.print();
            point_t A2{x+1, y-2, z};

            if(A2 == A1) {
                return  0;
            }

            line_t LL{A1, A2};
            LL.print();


        }

    return 0;
}


