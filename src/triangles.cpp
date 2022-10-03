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

vector_t::vector_t(const point_t &p1)
{
    std::vector<float> coord1 = p1.get_coord();
    x_ = coord1[0];
    y_ = coord1[1];
    z_ = coord1[2];

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

float vector_t::len() const
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
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

line_t::line_t(const plane_t &pl1, const plane_t &pl2)
{
    vector_t n1 = pl1.get_normal();
    vector_t n2 = pl2.get_normal();

    dv_ = vector_product(n1,n2);

    n1 /= n1.len();
    n2 /= n2.len();

    float n12_dot = dot_product(n1, n2);

    vector_t v1(pl1.get_point());
    vector_t v2(pl2.get_point());

    float c1 = dot_product(n1, v1);
    float c2 = dot_product(n2, v2);

    float a = (c2 * n12_dot - c1) / (n12_dot * n12_dot - 1);
    float b = (c1 * n12_dot - c2) / (n12_dot * n12_dot - 1);

    vector_t tmp(n1 * a + n2 * b);

    std::vector<float> coord = tmp.get_coord();

    p_ = point_t(coord[0], coord[1], coord[2]);
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

plane_t::plane_t(const triangle_t &t1)
{
    std::vector<point_t> points = t1.get_points();

    p_ = points[0];
    v1_ = vector_t(points[0], points[1]);
    v1_ = vector_t(points[0], points[2]);

}

point_t plane_t::get_point() const
{
    return p_;
}

vector_t plane_t::get_vector() const
{
    return v1_;
}

float geometry::dot_product(const vector_t &v1, const vector_t &v2)
{
    std::vector<float> coord_v1 = v1.get_coord();
    std::vector<float> coord_v2 = v2.get_coord();

    return coord_v1[0] * coord_v2[0] + coord_v1[1] * coord_v2[1] + coord_v1[2] * coord_v2[2];
}

vector_t geometry::vector_product(const vector_t &v1, const vector_t &v2)
{
    std::vector<float> coord_v1 = v1.get_coord();
    std::vector<float> coord_v2 = v2.get_coord();

    float x, y, z;
    x = coord_v1[1] * coord_v2[2] - coord_v1[2] * coord_v2[1];
    y = coord_v1[2] * coord_v2[0] - coord_v1[0] * coord_v2[3];
    z = coord_v1[0] * coord_v2[1] - coord_v1[1] * coord_v2[0];

    return  vector_t{x, y, z};

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

bool plane_t::is_equal(const plane_t &p) const
{
    vector_t n1 = get_normal();
    vector_t n2 = p.get_normal();

    vector_t mult = vector_product(n1, n2);

    vector_t v12(p_, p.p_);

    float dot1 = dot_product(v12, n1);
    float dot2 = dot_product(v12, n2);

    if(std::abs(dot1) < fit_tolerance && std::abs(dot2) < fit_tolerance && mult == 0)
        return true;

    return false;
}


std::vector<point_t> triangle_t::get_points() const
{
    std::vector<point_t> points;

    points.push_back(p1_);
    points.push_back(p2_);
    points.push_back(p3_);

    return points;
}

bool geometry::operator==(const point_t &p1, const point_t &p2) {
    return p2.is_equal(p1);
}

bool geometry::operator==(const vector_t &v1, const vector_t &v2) {
    return v1.is_equal(v2);
}

vector_t& vector_t::operator/=(float num)
{
    if(std::abs(num) >= fit_tolerance) {
        x_ = x_ / num;
        y_ = y_ / num;
        z_ = z_ / num;
    }

    return *this;
}

vector_t& vector_t::operator+=(const vector_t &v1)
{
    x_ = x_ + v1.x_;
    y_ = y_ + v1.y_;
    z_ = z_ + v1.z_;

    return *this;
}

vector_t geometry::operator+(const vector_t &v1, const vector_t &v2)
{
    vector_t res = v1;
    res += v2;
    return res;
}

float geometry::compute_distanse(const point_t &p, const plane_t &pl)
{
    point_t pl_p = pl.get_point();
    vector_t n = pl.get_normal();

    vector_t diff(p, pl_p);

    float dot = dot_product(diff, n);
    float n_len = n.len();

    return  dot / n_len;

}

float geometry::plane_to_point(const plane_t &pl, const point_t &p)
{
    point_t pl_point = pl.get_point();
    vector_t dif(p, pl_point);

    vector_t n = pl.get_normal();

    float distance = dot_product(n, dif) / n.len();

    return distance;

}

bool geometry::check_location(const plane_t &pl, const triangle_t &tr) {
    std::vector<point_t> points1 = tr.get_points();

    float dist1 = plane_to_point(pl, points1[0]);
    float dist2 = plane_to_point(pl, points1[1]);
    float dist3 = plane_to_point(pl, points1[2]);

    if ((dist1 < 0 && dist2 < 0 && dist3 < 0) ||
        (dist1 > 0 && dist2 > 0 && dist3 > 0)) {
        return false;
    }

    return true;
}

bool geometry::intersect(const triangle_t &t1, const triangle_t &t2)
{
    plane_t pl1(t1);
    plane_t pl2(t2);

    if(pl1.is_equal(pl2))
        return intersect_2D(t1, t2);

    if(pl1.is_parallel(pl2))
        return false;

    if(check_location(pl1, t2) || check_location(pl2, t1))  //all points on the same side of the plane
        return false;


    line_t intercection(pl1, pl2);

    return true;
}

bool geometry::intersect_2D(const triangle_t &t1, const triangle_t &t2)
{
    return true;
}