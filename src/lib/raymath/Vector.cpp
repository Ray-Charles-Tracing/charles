#include "../../include/raymath/Vector.hpp"

#include <cmath>

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(float iX, float iY, float iZ) : x(iX), y(iY), z(iZ) {}

Vector::~Vector() {}

float Vector::getX() const { return x; }
float Vector::getY() const { return y; }
float Vector::getZ() const { return z; }

void Vector::setX(float iX) { x = iX; }
void Vector::setY(float iY) { y = iY; }
void Vector::setZ(float iZ) { z = iZ; }

Vector Vector::operator+(Vector const &vect) const {
  Vector v;
  v.x = x + vect.x;
  v.y = y + vect.y;
  v.z = z + vect.z;
  return v;
}

Vector Vector::cross(Vector const &vect) const {
  Vector v;
  v.x = y * vect.z - z * vect.y;
  v.y = z * vect.x - x * vect.z;
  v.z = x * vect.y - y * vect.x;
  return v;
}

// Operator overload for scalar division
Vector Vector::operator/(float const &scalar) const {
  return Vector(x / scalar, y / scalar, z / scalar);
}

Vector Vector::operator*(float const &direction) const {
  Vector result;
  result.x = x * direction;
  result.y = y * direction;
  result.z = z * direction;
  return result;
}

float Vector::computeScalable(Vector const &vect) const {
  return ((x * vect.x) + (y * vect.y) + (z * vect.z));
}

Vector Vector::operator-(Vector const &vect) const {
  Vector v;
  v.x = x - vect.x;
  v.y = y - vect.y;
  v.z = z - vect.z;
  return v;
}

Vector &Vector::operator=(Vector const &vect) {
  x = vect.x;
  y = vect.y;
  z = vect.z;
  return *this;
}

std::ostream &operator<<(std::ostream &_stream, Vector const &vect) {
  return _stream << "(" << vect.x << "," << vect.y << "," << vect.z << ")";
}

float Vector::getNorm() const { return std::sqrt((x * x) + (y * y) + (z * z)); }

Vector Vector::normalize() const {
  Vector v;
  float length = getNorm();
  v.x = x / length;
  v.y = y / length;
  v.z = z / length;
  return v;
}
