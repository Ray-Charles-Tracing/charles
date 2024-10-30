#include "../../include/raymath/ShaderPhong.hpp"

#include <cmath>

Color ShaderPhong::calculateShader(
    Color pixel, std::optional<Shape::IntersectionResult> intersectionResultOpt,
    Ray ray, const Shape& shape, Light light) const {
  if (intersectionResultOpt.has_value()) {
    // Initialize variables
    Color shapeColor = shape.getColor();
    Color lightColor = light.getColor();
    Vector intersectionPoint = intersectionResultOpt.value().intersectPoint;
    Vector normal = intersectionResultOpt.value().normal;

    // Coefficient de réflexion diffuse et rugosité
    float k_d = shape.getDiffuseReflexionCoef();
    float roughness = shape.getRoughness();

    // Get bases diffuse values
    Vector lightDir, viewDir;
    std::tie(lightDir, viewDir) =
        this->getDiffuseBases(intersectionPoint, ray, shape, light);

    // Get bases diffuse values
    float diffuseIntensity;
    Color specularColor;
    std::tie(diffuseIntensity, specularColor) = this->getSpeculareBases(
        lightDir, normal, shape, viewDir, lightColor, light);

    // Ajuster l'intensité spéculaire en fonction de la rugosité
    float adjustedSpecularIntensity =
        specularColor.R();  // Utilisation du getter
    for (int i = 0; i < static_cast<int>(roughness * 10); ++i) {
      adjustedSpecularIntensity *= specularColor.R();  // Utilisation du getter
    }
    specularColor = Color(1.0f, 1.0f, 1.0f) * shape.getSpecularReflexionCoef() *
                    adjustedSpecularIntensity;

    // Calculate diffuse color
    Color diffuseColor = shapeColor * k_d * diffuseIntensity * lightColor;

    // Final color
    Color newPixel = pixel + diffuseColor + specularColor;

    return newPixel;
  }
  return pixel;
}
