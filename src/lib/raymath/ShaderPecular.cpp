#include "../../include/raymath/ShaderPecular.hpp"

#include <cmath>

#include "../../include/raymath/Color.hpp"

Color ShaderPecular::calculateShader(
    Color pixel, std::optional<Shape::IntersectionResult> intersectionResultOpt,
    Ray ray, const Shape& shape, Light light) const {
  if (intersectionResultOpt.has_value()) {
    // Initialize variables
    Color shapeColor = shape.getColor();
    Color lightColor = light.getColor();
    Vector intersectionPoint = intersectionResultOpt.value().intersectPoint;
    Vector normal = intersectionResultOpt.value().normal;

    // Get bases diffuse values
    Vector lightDir, viewDir;
    std::tie(lightDir, viewDir) =
        this->getDiffuseBases(intersectionPoint, ray, shape, light);

    // Get bases diffuse values
    float diffuseIntensity;
    Color specularColor;
    std::tie(diffuseIntensity, specularColor) = this->getSpeculareBases(
        lightDir, normal, shape, viewDir, lightColor, light);
    Color diffuseColor = shapeColor * diffuseIntensity;

    // Ajout des couleurs diffuse et spéculaire
    Color newPixel = pixel + diffuseColor + specularColor;

    return newPixel;
  }
  return pixel;
}
