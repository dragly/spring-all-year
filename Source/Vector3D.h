#ifndef VECTOR3D_H
#define VECTOR3D_H

// Based on Vector from pbrt.org

#include <ostream>
#include <cmath>

class Vector3D {
public:
    // Vector Public Methods
    inline Vector3D();
    inline Vector3D(float xx, float yy, float zz);
    inline Vector3D operator+(const Vector3D &v) const;

    inline Vector3D& operator+=(const Vector3D &v);
    inline Vector3D operator-(const Vector3D &v) const;

    inline Vector3D& operator-=(const Vector3D &v);
    inline Vector3D operator*(float f) const;

    inline Vector3D& operator*=(float f);
    inline Vector3D operator/(float f) const;

    inline Vector3D &operator/=(float f);
    inline Vector3D operator-() const;
    inline float operator[](int i) const;

    inline float &operator[](int i);
    inline float LengthSquared() const;
    inline float Length() const;

    inline bool operator==(const Vector3D &v) const;
    inline bool operator!=(const Vector3D &v) const;
    friend std::ostream& operator<< (std::ostream &out, const Vector3D &vector);

    // Vector Public Data
    float x, y, z;
};

Vector3D::Vector3D() { x = y = z = 0.f; }

Vector3D::Vector3D(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) {
}

Vector3D Vector3D::operator+(const Vector3D &v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D &Vector3D::operator+=(const Vector3D &v) {
    x += v.x; y += v.y; z += v.z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D &v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D &Vector3D::operator-=(const Vector3D &v) {
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

Vector3D Vector3D::operator*(float f) const { return Vector3D(f*x, f*y, f*z); }

Vector3D &Vector3D::operator*=(float f) {
    x *= f; y *= f; z *= f;
    return *this;
}

Vector3D Vector3D::operator/(float f) const {
    float inv = 1.f / f;
    return Vector3D(x * inv, y * inv, z * inv);
}

Vector3D &Vector3D::operator/=(float f) {
    float inv = 1.f / f;
    x *= inv; y *= inv; z *= inv;
    return *this;
}

Vector3D Vector3D::operator-() const { return Vector3D(-x, -y, -z); }

float Vector3D::operator[](int i) const {
    return (&x)[i];
}

float &Vector3D::operator[](int i) {
    return (&x)[i];
}

float Vector3D::LengthSquared() const { return x*x + y*y + z*z; }

float Vector3D::Length() const {
    return std::sqrt(LengthSquared());
}

bool Vector3D::operator==(const Vector3D &v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool Vector3D::operator!=(const Vector3D &v) const {
    return x != v.x || y != v.y || z != v.z;
}

#endif // VECTOR3D_H
