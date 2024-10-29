#include "../../include/raymath/ShaderFlat.hpp"

Color ShaderFlat::calculateShader(Color pixel,
                                  std::optional<Vector> intersectionPoint,
                                  Ray ray, Sphere sphere, Light light) const {
  if (intersectionPoint.has_value()) {
    Color newPixel = pixel;
    return pixel + sphere.getColor();
  }
  return pixel;
}
