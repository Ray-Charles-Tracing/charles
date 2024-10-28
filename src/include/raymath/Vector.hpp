#pragma once

#include <iostream>

class Vector {
 private:
  int x = 0;
  int y = 0;
  int z = 0;

 public:
  Vector();
  Vector(int x, int y, int z);
  ~Vector();

  int getX();
  int getY();
  int getZ();

  void setX(int x);
  void setY(int y);
  void setZ(int z);

  Vector operator+(Vector const& vect);
  Vector compMult(Vector const& vect);
  float operator*(Vector const& vect);
  Vector operator-(Vector const& vect);
  Vector operator=(Vector const& vect);
  friend std::ostream& operator<<(std::ostream& _stream, Vector const& vect);

  float getNorm();
  Vector normalize();
};
