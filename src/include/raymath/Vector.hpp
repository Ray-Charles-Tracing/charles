#pragma once

#include <iostream>

class Vector {
 private:
  float x = 0;
  float y = 0;
  float z = 0;

 public:
  Vector();
  Vector(float x, float y, float z);
  ~Vector();

  float getX() const;
  float getY() const;
  float getZ() const;

  void setX(float x);
  void setY(float y);
  void setZ(float z);

  Vector operator+(Vector const& vect) const;
  Vector operator*(float const& direction) const;
  float computeScalable(Vector const& vect) const;
  Vector operator-(Vector const& vect) const;
  Vector& operator=(Vector const& vect);
  friend std::ostream& operator<<(std::ostream& _stream, Vector const& vect);

  float getNorm() const;
  Vector normalize() const;
};