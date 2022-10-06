#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#define fit_tolerance 1e-5

namespace geometry {

    class triangle_t;
    class plane_t;
    class line_t;

    class point_t {
        float x_ = NAN, y_ = NAN, z_ = NAN;

    public:
        point_t(float x, float y, float z) : x_(x), y_(y), z_(z) {};
        point_t() = default;
        point_t(const plane_t &pl, const line_t &l);

        void print() const {
            std::cout << "(" << x_ << "; " << y_ << "; " << z_ << ")" << std::endl;
        }

        bool is_equal(const point_t &p1) const;
        std::vector<float> get_coord() const;
    };

    class vector_t {
        float x_ = NAN, y_ = NAN, z_ = NAN;

    public:
        vector_t() = default;
        vector_t(float n) : x_(n), y_(n), z_(n) {};
        vector_t(float x, float y, float z) : x_(x), y_(y), z_(z) {};
        vector_t(const point_t &p1);

        vector_t(const point_t &p1, const point_t &p2);

        void print() const {
            std::cout << "(" << x_ << "; " << y_ << "; " << z_ << ")" << std::endl;
        }

        bool is_equal(const vector_t &v1) const;
        std::vector<float> get_coord() const;

        float len() const;

        vector_t& operator/=(float num);
        vector_t& operator+=(const vector_t &v1);

        vector_t operator*(float num) const {
            return vector_t(x_ * num, y_ * num, z_ * num);
        }

    };

    class line_t {
        point_t p_;
        vector_t dv_; // directing vector

    public:
        line_t(const point_t &p1, const point_t &p2);
        line_t(const point_t &p, const vector_t &v);
        line_t(const plane_t &pl1, const plane_t &pl2);

        line_t() = default;

        void print() const {
            std::cout << "Point: ";
            p_.print();
            std::cout << "Directing vector ";
            dv_.print();
        }

        vector_t get_vector() const {return  dv_; };
        point_t get_point() const {return p_; };
    };

    class plane_t {
        point_t p_;
        vector_t v1_;
        vector_t v2_;
    public:
        plane_t() = default;
        plane_t(const point_t &p, const vector_t &v1, const vector_t &v2);
        plane_t(const point_t &p1, const point_t &p2, const point_t &p3);
        plane_t(const triangle_t &t1);

        void print() const {
            std::cout << "Point: ";
            p_.print();
            std::cout << "Vector1: ";
            v1_.print();
            std::cout << "Vector2: ";
            v2_.print();
        }

        bool is_equal(const plane_t &p) const;
        bool is_parallel(const plane_t &p) const;

        vector_t get_normal() const;
        vector_t get_vector() const;  //need?
        point_t get_point() const;

        line_t intersect(const plane_t &p) const;

    };

    class triangle_t {
        point_t p1_;
        point_t p2_;
        point_t p3_;

    public:
        triangle_t() = default;
        triangle_t(point_t &p1, point_t &p2, point_t &p3) : p1_(p1), p2_(p2), p3_(p3) {};

        std::vector<point_t> get_points() const;
    };

    vector_t vector_product(const vector_t &v1, const vector_t &v2);

    float dot_product(const vector_t &v1, const vector_t &v2);

    float compute_distanse(const point_t &p, const plane_t &pl);

    bool operator==(const point_t &p1, const point_t &p2);

    bool operator==(const vector_t &v1, const vector_t &v2);

    vector_t operator+(const vector_t &v1, const vector_t &v2);

    float plane_to_point(const plane_t &pl, const point_t &p);

    bool check_location(const plane_t &pl, const triangle_t &tr);

    std::pair<line_t, line_t> triangle_plane_intersect(const triangle_t &tr, const plane_t &pl);

    triangle_t project_to_XY(const triangle_t &tr1);

    std::vector<float> compute_intervals(const line_t &l, const triangle_t &tr1, const triangle_t &tr2);

    float compute_t_param(const point_t &p, const line_t &l);

    bool intersect(const triangle_t &t1, const triangle_t &t2);

    bool intersect_2D(const triangle_t &t1, const triangle_t &t2);
}