#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#define fit_tolerance 1e-5

namespace geometry {
    class point_t {
        float x_ = NAN, y_ = NAN, z_ = NAN;

    public:
        point_t(float x, float y, float z) : x_(x), y_(y), z_(z) {};
        point_t() = default;

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

        vector_t(const point_t &p1, const point_t &p2);

        void print() const {
            std::cout << "(" << x_ << "; " << y_ << "; " << z_ << ")" << std::endl;
        }

        bool is_equal(const vector_t &v1) const;
        std::vector<float> get_coord() const;

    };

    class line_t {
        point_t p_;
        vector_t dv_; // directing vector

    public:
        line_t(const point_t &p1, const point_t &p2);
        line_t(const point_t &p, const vector_t &v);

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

    };

    vector_t vector_product(const vector_t &v1, const vector_t &v2);

    bool operator==(const point_t &p1, const point_t &p2);

    bool operator==(const vector_t &v1, const vector_t &v2);
}