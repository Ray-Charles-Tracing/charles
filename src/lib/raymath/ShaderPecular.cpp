#include "../../include/raymath/ShaderPecular.hpp"

#include <cmath>

#include "../../include/raymath/Color.hpp"

Color ShaderPecular::calculateShader(Color pixel,
                                     std::optional<Vector> intersectionPointOpt,
                                     Ray ray, const Shape& shape,
                                     Light light) const {
  if (intersectionPointOpt.has_value()) {
    Color shapeColor = shape.getColor();
    Color lightColor = light.getColor();

    // Get bases diffuse values
    Vector intersectionPoint, normal, lightDir, viewDir;
    std::tie(intersectionPoint, normal, lightDir, viewDir) =
        this->getDiffuseBases(*intersectionPointOpt, ray, shape, light);

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
