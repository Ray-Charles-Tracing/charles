#include "../../include/raymath/ShaderFlat.hpp"

Color ShaderFlat::calculateShader(Color pixel, Ray ray, Sphere sphere) const {
  Vector P(6, 7, 8);
  /*   if (P) {
      return pixel;
    } */
  Color newPixel = pixel;
  return pixel + sphere.getColor();
}
