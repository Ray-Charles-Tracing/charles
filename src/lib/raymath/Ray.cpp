#include "../../include/raymath/Ray.hpp"

Ray::Ray(Vector iVectorOrigin, Vector iVectorDirection)
    : origin(iVectorOrigin) {
  direction = iVectorDirection.normalize();
}

Ray::~Ray() {}

Vector Ray::getOrigin() const { return origin; }
Vector Ray::getDirection() const { return direction; }
