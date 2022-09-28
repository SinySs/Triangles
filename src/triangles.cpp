#include "triangle.h"

using namespace geometry;

std::vector<float> point_t::get_coord() const
{
    std::vector<float> coord = {x_, y_, z_};
    return coord;
}

bool point_t::is_equal(const point_t &p1) const
{
    if(std::abs(x_ -  p1.x_) < fit_tolerance
        && std::abs(y_ -  p1.y_) < fit_tolerance
        && std::abs(z_ -  p1.z_) < fit_tolerance) {

        return true;
    }

    return false;
}

vector_t::vector_t(const point_t &p1, const point_t &p2)
{
    std::vector<float> coord1 = p1.get_coord();
    std::vector<float> coord2 = p2.get_coord();

    x_ = coord1[0] - coord2[0];
    y_ = coord1[1] - coord2[1];
    z_ = coord1[2] - coord2[2];
}


bool vector_t::is_equal(const geometry::vector_t &v1) const
{
    if(std::abs(x_ - v1.x_) < fit_tolerance
        && std::abs(y_ - v1.y_) < fit_tolerance
        && std::abs(z_ - v1.z_) < fit_tolerance) {

        return true;
    }

    return false;

}

std::vector<float> vector_t::get_coord() const
{
    std::vector<float> coord {x_, y_, z_};
    return coord;
}

line_t::line_t(const point_t &p1, const point_t &p2)
{
    p_ = p1;
    dv_ = vector_t(p1, p2);
}

line_t::line_t(const point_t &p, const vector_t &v)
{
    dv_ = v;
    p_ = p;
}

plane_t::plane_t(const point_t &p, const vector_t &v1, const vector_t &v2)
{
    p_ = p;
    v1_ = v1;
    v2_ = v2;
}

plane_t::plane_t(const point_t &p1, const point_t &p2, const point_t &p3)
{
    p_ = p1;
    v1_ = vector_t(p1, p2);
    v2_ = vector_t(p1, p3);
}

point_t plane_t::get_point() const
{
    return p_;
}

vector_t plane_t::get_vector() const
{
    return v1_;
}


vector_t geometry::vector_product(const vector_t &v1, const vector_t &v2)
{
    std::vector<float> coord_v1 = v1.get_coord();
    std::vector<float> coord_v2 = v2.get_coord();

    float x, y, z;
    x = coord_v1[1] * coord_v2[2] - coord_v1[2] * coord_v2[1];
    y = coord_v1[2] * coord_v2[0] - coord_v1[0] * coord_v2[3];
    z = coord_v1[0] * coord_v2[1] - coord_v1[1] * coord_v2[0];

    return  vector_t(x, y, z);

}

vector_t plane_t::get_normal() const
{
    vector_t normal;
    normal = vector_product(v1_, v2_);

    return  normal;
}

bool plane_t::is_parallel(const plane_t &p) const
{
    vector_t v1 = get_normal();
    vector_t v2 = p.get_normal();

    vector_t mult = vector_product(v1, v2);

    if(mult == 0)
        return true;

    return false;

}

bool geometry::operator==(const point_t &p1, const point_t &p2) {
    return p2.is_equal(p1);
}

bool geometry::operator==(const vector_t &v1, const vector_t &v2) {
    return v1.is_equal(v2);
}
