#include "../../include/raymath/Ray.hpp"

Ray::Ray(Vector iVectorOrigin, Vector iVectorDirection)
    : origin(iVectorOrigin) {
  direction = iVectorDirection.normalize();
}

Ray::~Ray() {}

Vector Ray::getOrigin() const { return origin; }        // Add const
Vector Ray::getDirection() const { return direction; }  // Add const