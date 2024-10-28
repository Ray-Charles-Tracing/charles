#include "../../include/raymath/Vector.hpp"

#include <cmath>

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(float iX, float iY, float iZ) : x(iX), y(iY), z(iZ) {}

Vector::~Vector() {}

float Vector::getX() { return x; }
float Vector::getY() { return y; }
float Vector::getZ() { return z; }

void Vector::setX(float iX) { x = iX; }
void Vector::setY(float iY) { y = iY; }
void Vector::setZ(float iZ) { z = iZ; }

Vector Vector::operator+(Vector const &vect) {
  Vector v;
  v.x = x + vect.x;
  v.y = y + vect.y;
  v.z = z + vect.z;
  return v;
}

Vector Vector::operator*(Vector const &vect) {
  Vector result;
  result.x = x * vect.x;
  result.y = y * vect.y;
  result.z = z * vect.z;
  return result;
}

float Vector::computeScalable(Vector const &vect) {
  return ((x * vect.x) + (y * vect.y) + (z * vect.z));
}

Vector Vector::operator-(Vector const &vect) {
  Vector v;
  v.x = x - vect.x;
  v.y = y - vect.y;
  v.z = z - vect.z;
  return v;
}

Vector Vector::operator=(Vector const &vect) {
  x = vect.x;
  y = vect.y;
  z = vect.z;
  return *this;
}

std::ostream &operator<<(std::ostream &_stream, Vector const &vect) {
  return _stream << "(" << vect.x << "," << vect.y << "," << vect.z << ")";
}

float Vector::getNorm() { return std::sqrt((x * x) + (y * y) + (z * z)); }

Vector Vector::normalize() {
  Vector v;
  float length = getNorm();
  if (length == 0) {
    return Vector(0, 0, 0);
  }
  v.x = x / length;
  v.y = y / length;
  v.z = z / length;
  return v;
}
