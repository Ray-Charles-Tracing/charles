#include "../../include/raymath/ShaderDiffus.hpp"

#include "../../include/raymath/Color.hpp"

Color ShaderDiffus::calculateShader(
    Color pixel, std::optional<Shape::IntersectionResult> intersectionResultOpt,
    Ray ray, const Shape& shape, Light light) const {
  if (intersectionResultOpt.has_value()) {
    // Initialize variables
    Vector intersectionPoint = intersectionResultOpt.value().intersectPoint;
    Vector normal = intersectionResultOpt.value().normal;
    Color shapeColor = shape.getColor();

    // Get bases diffuse values
    Vector lightDir, viewDir;
    std::tie(lightDir, viewDir) =
        this->getDiffuseBases(intersectionPoint, ray, shape, light);

    float intensity = normal.computeScalable(lightDir);

    // Utilisation de l'opérateur * pour multiplier l'intensité avec la couleur
    // de la sphère
    Color intensityColor = shapeColor * intensity;

    Color newPixel = pixel + intensityColor;

    return newPixel;
  }
  return pixel;
}
