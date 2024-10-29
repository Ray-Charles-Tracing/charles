#include "../../include/raymath/ShaderPhong.hpp"

#include <cmath>

Color ShaderPhong::calculateShader(Color pixel,
                                   std::optional<Vector> intersectionPointOpt,
                                   Ray ray, Sphere sphere, Light light) const {
  if (intersectionPointOpt.has_value()) {
    Vector intersectionPoint = *intersectionPointOpt;
    Vector spherePos = sphere.getPosition();
    Vector cp = intersectionPoint - spherePos;
    Vector normal = cp.normalize();

    Vector lightDir = (light.getPosition() - intersectionPoint).normalize();
    Vector viewDir = (ray.getOrigin() - intersectionPoint).normalize();

    // Calcul de la réflexion
    Vector reflection =
        (normal * (2 * normal.computeScalable(lightDir)) - lightDir)
            .normalize();

    // Coefficients de réflexion
    float k_d = 0.5f;  // Coefficient de réflexion diffuse // Material
    float k_s = 0.8f;  // Coefficient de réflexion spéculaire // Material
    float alpha =
        32.0f;  // Exposant pour contrôler la "taille" de la brillance // Light

    // Calcul de l'intensité diffuse
    float diffuseIntensity = std::max(0.0f, normal.computeScalable(lightDir));
    Color sphereColor = sphere.getColor();
    Color lightColor = light.getColor();
    Color diffuseColor = sphereColor * k_d * diffuseIntensity * lightColor;

    // Calcul de l'intensité spéculaire
    float specularIntensity =
        std::pow(std::max(0.0f, reflection.computeScalable(viewDir)), alpha);
    Color specularColor =
        Color(1.0f, 1.0f, 1.0f) * k_s * specularIntensity * lightColor;

    // Couleur finale
    Color newPixel = pixel + diffuseColor + specularColor;

    return newPixel;
  }
  return pixel;
}
