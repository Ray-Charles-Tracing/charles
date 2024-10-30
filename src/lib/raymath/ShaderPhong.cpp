#include "../../include/raymath/ShaderPhong.hpp"

#include <cmath>

Color ShaderPhong::calculateShader(Color pixel,
                                   std::optional<Vector> intersectionPointOpt,
                                   Ray ray, const Shape& shape,
                                   Light light) const {
  if (intersectionPointOpt.has_value()) {
    Color shapeColor = shape.getColor();
    Color lightColor = light.getColor();

    // Coefficient de réflexion diffuse
    float k_d = shape.getDiffuseReflexionCoef();

    // Get bases diffuse values
    Vector intersectionPoint, normal, lightDir, viewDir;
    std::tie(intersectionPoint, normal, lightDir, viewDir) =
        this->getDiffuseBases(*intersectionPointOpt, ray, shape, light);

    // Get bases diffuse values
    float diffuseIntensity;
    Color specularColor;
    std::tie(diffuseIntensity, specularColor) = this->getSpeculareBases(
        lightDir, normal, shape, viewDir, lightColor, light);

    // Obtenir la rugosité
    float roughness = shape.getRoughness();

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
