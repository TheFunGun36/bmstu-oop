#include "pch.h"
#include "jvector3d.h"
#include <sstream>

namespace Jora {

Vector3D::Vector3D(real x, real y, real z) noexcept {
    setX(x);
    setY(y);
    setZ(z);
}

real Vector3D::operator[](size_t index) const {
    if (index < 0 || index > 2)
        throw CoordsOutOfRange(__FILE__, __FUNCTION__, __LINE__);
    return _value[index];
}

real& Vector3D::operator[](size_t index) {
    if (index < 0 || index > 2)
        throw CoordsOutOfRange(__FILE__, __FUNCTION__, __LINE__);
    return _value[index];
}

real Vector3D::operator[](Axis axis) const {
    return (*this)[int(axis)];
}

real& Vector3D::operator[](Axis axis) {
    return (*this)[int(axis)];
}

real Vector3D::x() const noexcept {
    return _value[0];
}

real Vector3D::y() const noexcept {
    return _value[1];
}

real Vector3D::z() const noexcept {
    return _value[2];
}

real& Vector3D::x() noexcept {
    return _value[0];
}

real& Vector3D::y() noexcept {
    return _value[1];
}

real& Vector3D::z() noexcept {
    return _value[2];
}

Vector3D& Vector3D::setX(real value) noexcept {
    x() = value;
    return *this;
}

Vector3D& Vector3D::setY(real value) noexcept {
    y() = value;
    return *this;
}

Vector3D& Vector3D::setZ(real value) noexcept {
    z() = value;
    return *this;
}

Vector3D& Vector3D::operator=(const Vector3D& other) noexcept {
    setX(other.x());
    setY(other.y());
    setZ(other.z());
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& other) noexcept {
    x() += other.x();
    y() += other.y();
    z() += other.z();
    return *this;
}

Vector3D& Vector3D::operator+=(real value) noexcept {
    x() += value;
    y() += value;
    z() += value;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other) noexcept {
    return *this += -other;
}

Vector3D& Vector3D::operator-=(real value) noexcept {
    return *this += -value;
}

Vector3D& Vector3D::operator*=(real value) noexcept {
    x() *= value;
    y() *= value;
    z() *= value;
    return *this;
}

Vector3D& Vector3D::operator/=(real value) noexcept {
    x() /= value;
    y() /= value;
    z() /= value;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& other) const noexcept {
    Vector3D result(*this);
    result += other;
    return result;
}

Vector3D Vector3D::operator+(real value) const noexcept {
    Vector3D result(*this);
    result += value;
    return result;
}

Vector3D Vector3D::operator-(const Vector3D& other) const noexcept {
    return *this + -other;
}

Vector3D Vector3D::operator-(real value) const noexcept {
    return *this + -value;
}

Vector3D Vector3D::operator*(real value) const noexcept {
    Vector3D result(*this);
    result *= value;
    return result;
}

Vector3D Vector3D::operator/(real value) const noexcept {
    Vector3D result(*this);
    result /= value;
    return result;
}

Vector3D Vector3D::operator-() const noexcept {
    return Vector3D(-x(), -y(), -z());
}

bool Vector3D::operator==(const Vector3D& other) const noexcept {
    return realEq(x(), other.x()) && realEq(y(), other.y()) && realEq(z(), other.z());
}

bool Vector3D::operator!=(const Vector3D& other) const noexcept {
    return !(*this == other);
}

Vector3D::operator bool() {
    return *this != Vector3D();
}

Axis Vector3D::nextAxis(Axis value) {
    return Axis(nextAxis(int(value)));
}

Axis Vector3D::prevAxis(Axis value) {
    return Axis(prevAxis(int(value)));
}

int Vector3D::nextAxis(int axis) {
    return axis == 2 ? 0 : axis + 1;
}
int Vector3D::prevAxis(int axis) {
    return axis ? axis - 1 : 2;
}
std::ostream& Vector3D::addToStream(std::ostream& stream) const {
    return stream << "(" << x() << ", " << y() << ", " << z() << ")";
}

std::wostream& Vector3D::addToStream(std::wostream& stream) const {
    return stream << L"(" << x() << L", " << y() << L", " << z() << L")";
}

}
