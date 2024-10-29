#pragma once

#include <iostream>

#include "../raymath/Vector.hpp"

class Ray {
 private:
  Vector origin;
  Vector direction;

 public:
  Ray(Vector origin, Vector direction);
  ~Ray();

  Vector getOrigin() const;     // Add const
  Vector getDirection() const;  // Add const
};