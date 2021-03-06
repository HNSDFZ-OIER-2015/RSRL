//
// Copyright 2016 riteme
//

#include "Math.h"
#include "Defs.h"

#include <cmath>
#include <cstddef>
#include <cstring>

namespace rsr {

Vector4f::Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Vector4f::Vector4f(const float _x, const float _y, const float _z)
    : x(_x), y(_y), z(_z), w(1.0f) {}

Vector4f::Vector4f(const float _x, const float _y, const float _z,
                   const float _w)
    : x(_x), y(_y), z(_z), w(_w) {}

Vector4f Vector4f::operator+(const Vector4f &b) const {
    return Vector4f(x + b.x, y + b.y, z + b.z);
}

Vector4f Vector4f::operator-(const Vector4f &b) const {
    return Vector4f(x - b.x, y - b.y, z - b.z);
}

Vector4f Vector4f::operator*(const float b) const {
    return Vector4f(x * b, y * b, z * b);
}

Vector4f operator*(const float b, const Vector4f &a) {
    return a * b;
}

Vector4f Vector4f::operator-() const {
    return Vector4f(-x, -y, -z);
}

Vector4f &Vector4f::operator+=(const Vector4f &b) {
    *this = *this + b;

    return *this;
}

Vector4f &Vector4f::operator-=(const Vector4f &b) {
    *this = *this - b;

    return *this;
}

Vector4f &Vector4f::operator*=(const float b) {
    *this = *this * b;

    return *this;
}

float Vector4f::length() const {
    return sqrt(x * x + y * y + z * z);
}

Matrix4f::Matrix4f() {
    memset(_mat, 0, sizeof(_mat));
}

Matrix4f::Matrix4f(const float m00, const float m01, const float m02,
                   const float m03, const float m10, const float m11,
                   const float m12, const float m13, const float m20,
                   const float m21, const float m22, const float m23,
                   const float m30, const float m31, const float m32,
                   const float m33) {
    _mat[0][0] = m00;
    _mat[0][1] = m01;
    _mat[0][2] = m02;
    _mat[0][3] = m03;
    _mat[1][0] = m10;
    _mat[1][1] = m11;
    _mat[1][2] = m12;
    _mat[1][3] = m13;
    _mat[2][0] = m20;
    _mat[2][1] = m21;
    _mat[2][2] = m22;
    _mat[2][3] = m23;
    _mat[3][0] = m30;
    _mat[3][1] = m31;
    _mat[3][2] = m32;
    _mat[3][3] = m33;
}

float *Matrix4f::operator[](const size_t x) {
    ASSERTF(x < 4, "Invalid argument x: expected in [0, 3], got %zu.", x);

    return &_mat[x][0];
}

const float *Matrix4f::operator[](const size_t x) const {
    ASSERTF(x < 4, "Invalid argument x: expected in [0, 3], got %zu.", x);

    return &_mat[x][0];
}

Matrix4f Matrix4f::operator+(const Matrix4f &b) const {
    Matrix4f c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = _mat[i][j] + b[i][j];

    return c;
}

Matrix4f Matrix4f::operator-(const Matrix4f &b) const {
    Matrix4f c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = _mat[i][j] - b[i][j];

    return c;
}

Matrix4f Matrix4f::operator*(const Matrix4f &b) const {
    Matrix4f c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            for (size_t k = 0; k < 4; k++)
                c[i][j] += _mat[i][k] * b[k][j];

    return c;
}

Matrix4f Matrix4f::operator*(const float b) const {
    Matrix4f c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = _mat[i][j] * b;

    return c;
}

Vector4f Matrix4f::operator*(const Vector4f &b) const {
    return Vector4f(b.x * _mat[0][0] + b.y * _mat[1][0] + b.z * _mat[2][0] +
                        b.w * _mat[3][0],
                    b.x * _mat[0][1] + b.y * _mat[1][1] + b.z * _mat[2][1] +
                        b.w * _mat[3][1],
                    b.x * _mat[0][2] + b.y * _mat[1][2] + b.z * _mat[2][2] +
                        b.w * _mat[3][2],
                    b.x * _mat[0][3] + b.y * _mat[1][3] + b.z * _mat[2][3] +
                        b.w * _mat[3][3]);
}

Matrix4f Matrix4f::operator-() const {
    Matrix4f c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = -_mat[i][j];

    return c;
}

Matrix4f operator*(const float b, const Matrix4f &a) {
    return a * b;
}

Matrix4f &Matrix4f::operator+=(const Matrix4f &b) {
    *this = *this + b;

    return *this;
}

Matrix4f &Matrix4f::operator-=(const Matrix4f &b) {
    *this = *this - b;

    return *this;
}

Matrix4f &Matrix4f::operator*=(const Matrix4f &b) {
    *this = *this * b;

    return *this;
}

Matrix4f &Matrix4f::operator*=(const float b) {
    *this = *this * b;

    return *this;
}

Vector4f normalize(const Vector4f &vec) {
    return vec * (1.0f / vec.length());
}

float cross(const Vector4f &a, const Vector4f &b) {
    return a.x * b.y - a.y * b.x;
}

float dot(const Vector4f &a, const Vector4f &b) {
    return a.x * a.y + b.x * b.y;
}

Matrix4f identity() {
    return Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,  // Line 1
                    0.0f, 1.0f, 0.0f, 0.0f,  // Line 2
                    0.0f, 0.0f, 1.0f, 0.0f,  // Line 3
                    0.0f, 0.0f, 0.0f, 1.0f   // Line 4
                    );
}

Matrix4f transform(const float dx, const float dy, const float dz) {
    return Matrix4f(1.0f, 0.0f, 0.0f, dx,   // Line 1
                    0.0f, 1.0f, 0.0f, dy,   // Line 2
                    0.0f, 0.0f, 1.0f, dz,   // Line 3
                    0.0f, 0.0f, 0.0f, 1.0f  // Line 4
                    );
}

Matrix4f transform(const Vector4f &d) {
    return transform(d.x, d.y, d.z);
}

Matrix4f scale(const float sx, const float sy, const float sz) {
    return Matrix4f(sx, 0.0f, 0.0f, 0.0f,   // Line 1
                    0.0f, sy, 0.0f, 0.0f,   // Line 2
                    0.0f, 0.0f, sz, 0.0f,   // Line 3
                    0.0f, 0.0f, 0.0f, 1.0f  // Line 4
                    );
}
Matrix4f scale(const Vector4f s) {
    return scale(s.x, s.y, s.z);
}

Matrix4f rotate_y(const float angle) {
    return Matrix4f(cos(angle), 0.0f, -sin(angle), 0.0f,  // Line 1
                    0.0f, 1.0f, 0.0f, 0.0f,               // Line 2
                    sin(angle), 0.0f, cos(angle), 0.0f,   // Line 3
                    0.0f, 0.0f, 0.0f, 1.0f                // Line 4
                    );
}
Matrix4f rotate_x(const float angle) {
    return Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,               // Line 1
                    0.0f, cos(angle), -sin(angle), 0.0f,  // Line 2
                    0.0f, sin(angle), cos(angle), 0.0f,   // Line 3
                    0.0f, 0.0f, 0.0f, 1.0f                // Line 4
                    );
}

Matrix4f rotate_z(const float angle) {
    return Matrix4f(cos(angle), -sin(angle), 0.0f, 0.0f,  // Line 1
                    sin(angle), cos(angle), 0.0f, 0.0f,   // Line 2
                    0.0f, 0.0f, 1.0f, 0.0f,               // Line 3
                    0.0f, 0.0f, 0.0f, 1.0f                // Line 4
                    );
}

}  // namespace rsr
