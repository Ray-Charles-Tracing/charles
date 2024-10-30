#include "../../include/raymath/ShaderFlat.hpp"

Color ShaderFlat::calculateShader(
    Color pixel, std::optional<Shape::IntersectionResult> intersectionResultOpt,
    Ray ray, const Shape& shape, Light light) const {
  if (intersectionResultOpt.has_value()) {
    Color newPixel = pixel;
    return pixel + shape.getColor();
  }
  return pixel;
}