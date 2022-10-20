#include "triangle.h"

using namespace geometry;

point_t::point_t(const plane_t &pl, const line_t &l)
{
    vector_t n = pl.get_normal();
    vector_t dv = l.get_vector();

    point_t line_point =  l.get_point();

    vector_t v_l(line_point);
    vector_t v_p(pl.get_point());

    float d = (-1) * dot_product(n, v_p);

    float t = (-1) * (dot_product(n, v_l) + d)  / dot_product(n, dv);

    vector_t q = dv * t;
    std::vector<float> coord = q.get_coord();

    x_ = line_point.x_ + coord[0];
    y_ = line_point.y_ + coord[1];
    z_ = line_point.z_ + coord[2];

}

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
    v2_ = vector_t(points[0], points[2]);

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
    y = coord_v1[2] * coord_v2[0] - coord_v1[0] * coord_v2[2];
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
    point_t pl_point = pl.get_point();
    vector_t n = pl.get_normal();

    vector_t diff(p, pl_point);

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
        return true;
    }

    return false;
}

std::pair<line_t, line_t> geometry::triangle_plane_intersect(const triangle_t &tr, const plane_t &pl)
{
    std::vector<point_t> tr_points = tr.get_points();

    float dist1 = compute_distanse(tr_points[0], pl);
    float dist2 = compute_distanse(tr_points[1], pl);
    float dist3 = compute_distanse(tr_points[2], pl);

    line_t l1, l2;

    if((dist1 > 0 && dist2 > 0 && dist3 < 0) || (dist1 < 0 && dist2 < 0 && dist3 > 0)) {
        l1 = line_t(tr_points[2], tr_points[1]);
        l2 = line_t(tr_points[2], tr_points[0]);

    } else if((dist1 > 0 && dist2 < 0 && dist3 > 0) || (dist1 < 0 && dist2 > 0 && dist3 < 0)) {
        l1 = line_t(tr_points[1], tr_points[0]);
        l2 = line_t(tr_points[1], tr_points[2]);

    } else if((dist1 > 0 && dist2 < 0 && dist3 < 0) || (dist1 < 0 && dist2 > 0 && dist3 > 0)) {
        l1 = line_t(tr_points[0], tr_points[1]);
        l2 = line_t(tr_points[0], tr_points[2]);
    }

    if(std::abs(dist1) < fit_tolerance) {
        l1 = line_t(tr_points[0], tr_points[1]);
        l2 = line_t(tr_points[0], tr_points[2]);

    } else if(std::abs(dist2) < fit_tolerance) {
        l1 = line_t(tr_points[1], tr_points[0]);
        l2 = line_t(tr_points[1], tr_points[2]);

    } else if(std::abs(dist3) < fit_tolerance) {
        l1 = line_t(tr_points[2], tr_points[1]);
        l2 = line_t(tr_points[2], tr_points[0]);
    }

    return std::make_pair(l1, l2);
}

float geometry::compute_t_param(const point_t &p, const line_t &l)
{
    vector_t dv = l.get_vector();
    point_t l_point = l.get_point();
    vector_t diff(p, l_point);

    std::vector<float> diff_coord = diff.get_coord();
    std::vector<float> dv_coord = dv.get_coord();

    float tx = diff_coord[0] / dv_coord[0];

    return tx;
}

std::vector<float> geometry::compute_intervals(const line_t &l, const triangle_t &tr1, const triangle_t &tr2)
{
    plane_t pl1(tr1);
    plane_t pl2(tr2);

    std::pair<line_t, line_t> lines = triangle_plane_intersect(tr1, pl2);

    point_t intersection_p1(pl1, lines.first);
    point_t intersection_p2(pl1, lines.second);

    float t00 = compute_t_param(intersection_p1, l);
    float t01 = compute_t_param(intersection_p2, l);

    lines = triangle_plane_intersect(tr2, pl1);

    intersection_p1 = point_t(pl2, lines.first);
    intersection_p2 = point_t(pl1, lines.second);

    float t10 = compute_t_param(intersection_p1, l);
    float t11 = compute_t_param(intersection_p2, l);

    std::vector<float> ret_intervals{t00, t01, t10, t11};

    return ret_intervals;

}

bool geometry::intersect(const triangle_t &tr1, const triangle_t &tr2)
{
    plane_t pl1(tr1);
    plane_t pl2(tr2);

    if(pl1.is_equal(pl2))
        return intersect_2D(tr1, tr2);

    if(pl1.is_parallel(pl2))
        return false;

    if(check_location(pl1, tr2) || check_location(pl2, tr1))  //all points on the same side of the plane
        return false;

    line_t intercection_line(pl1, pl2);
    std::vector<float> t_params = compute_intervals(intercection_line, tr1, tr2);

    float t00 = t_params[0];
    float t01 = t_params[1];
    float t10 = t_params[2];
    float t11 = t_params[3];

    if((std::min(t00, t01) > std::max(t10, t11)) || (std::min(t10,t11) > std::max(t00,t01)))
        return false;

    return true;

}
point_t project_point(const point_t &p, int n_pl)
{
    std::vector<float> coord = p.get_coord();
    coord[n_pl] = 0;

    return point_t(coord[0], coord[1], coord[2]);
}


triangle_t geometry::project_to_XY(const triangle_t &tr1)
{
    plane_t pl(tr1);

    vector_t normal = pl.get_normal();
    std::vector<float> coord = normal.get_coord();

    std::vector<point_t> points = tr1.get_points();
    std::vector<point_t> proj_p;

    if(std::abs(coord[0]) < fit_tolerance && std::abs(coord[2]) < fit_tolerance) { //in OXZ
        for(int i = 0; i < 3; i++) {
            point_t new_p = points[i];
            std::vector<float> coord_new_p = new_p.get_coord();
            std::swap(coord_new_p[1], coord_new_p[2]); // cange OXZ to OXY

            proj_p.push_back(point_t(coord_new_p[0], coord_new_p[1], coord_new_p[2]));
        }
    } else if(coord[2] == 0) { // perpendicular to OXY
        for(int i = 0; i < 3; i++) {
            point_t new_p = project_point(points[i], 0);
            std::vector<float> coord_new_p = new_p.get_coord();
            std::swap(coord_new_p[0], coord_new_p[2]); // cange OZY to OXY

            proj_p.push_back(point_t(coord_new_p[0], coord_new_p[1], coord_new_p[2]));
        }
    } else {
        for(int i = 0; i < 3; i++) {
            proj_p.push_back(project_point(points[i], 2));
        }
    }

    return triangle_t(proj_p[0], proj_p[1], proj_p[2]);


}

void compute_interval(const triangle_t &tr, vector_t D, float& min, float& max)
{
    std::vector<point_t> points = tr.get_points();

    vector_t V(points[0]);
    min = max = dot_product(D, V);
    for (int i = 1; i < 3; i++) {
        V = vector_t(points[i]);
        float value = dot_product(D, V);
        if (value < min)
            min = value;
        else if (value > max)
            max = value;
    }
}

bool geometry::intersect_2D(const triangle_t &tr1, const triangle_t &tr2)
{
    triangle_t projection1 = project_to_XY(tr1);
    triangle_t projection2 = project_to_XY(tr2);

    std::vector<point_t> points1 = projection1.get_points();
    std::vector<point_t> points2 = projection2.get_points();

    float min0, max0, min1, max1;

    for (int i0 = 0, i1 = 2; i0 < 3; i1 = i0, i0++) {
        vector_t D(points1[i0], points1[i1]);
        compute_interval(tr1, D, min0, max0);
        compute_interval(tr2, D, min1, max1);
        if (max1 < min0 || max0 < min1)
            return false;
    }

    for (int i0 = 0, i1 = 2; i0 < 3; i1 = i0, i0++) {
        vector_t D(points2[i0], points2[i1]);
        compute_interval(tr1, D, min0, max0);
        compute_interval(tr2, D, min1, max1);
        if (max1 < min0 || max0 < min1)
            return false;
    }

    return true;
}