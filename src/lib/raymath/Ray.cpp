#include "../../include/raymath/Ray.hpp"

Ray::Ray(Vector iVectorOrigin, Vector iVectorDirection)
    : origin(iVectorOrigin), direction(iVectorDirection) {}

Ray::~Ray() {}

Vector Ray::getOrigin() { return origin; }
Vector Ray::getDirection() { return direction; }
