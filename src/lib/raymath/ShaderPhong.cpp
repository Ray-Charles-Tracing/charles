#include "../../include/raymath/ShaderPhong.hpp"

#include <cmath>

Color ShaderPhong::calculateShader(Color pixel,
                                   std::optional<Vector> intersectionPointOpt,
                                   Ray ray, const Shape& shape,
                                   Light light) const {
  if (intersectionPointOpt.has_value()) {
    Color shapeColor = shape.getColor();
    Color lightColor = light.getColor();

    // Reflexion coef
    float k_d =
        shape.getDiffuseReflexionCoef();  // Coefficient de réflexion diffuse
                                          // shape.getDiffusReflexionCoef

    // Get bases diffuse values
    Vector intersectionPoint, normal, lightDir, viewDir;
    std::tie(intersectionPoint, normal, lightDir, viewDir) =
        this->getDiffuseBases(*intersectionPointOpt, ray, shape, light);

    // Get bases diffuse values
    float diffuseIntensity;
    Color specularColor;
    std::tie(diffuseIntensity, specularColor) = this->getSpeculareBases(
        lightDir, normal, shape, viewDir, lightColor, light);

    // Calculate diffuse color
    Color diffuseColor = shapeColor * k_d * diffuseIntensity * lightColor;

    // Final color
    Color newPixel = pixel + diffuseColor + specularColor;

    return newPixel;
  }
  return pixel;
}
