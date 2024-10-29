#include "../../include/raymath/ShaderPecular.hpp"

#include <cmath>

#include "../../include/raymath/Color.hpp"

Color ShaderPecular::calculateShader(Color pixel,
                                     std::optional<Vector> intersectionPointOpt,
                                     Ray ray, Sphere sphere,
                                     Light light) const {
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

    // Coefficient de réflexion spéculaire et exposant
    float k_s = 0.5f;
    float alpha = 32.0f;

    // Calcul de l'intensité spéculaire
    float specularIntensity =
        std::pow(std::max(0.0f, reflection.computeScalable(viewDir)),
                 alpha);  // Intensité du reflet produit

    // Calcul de la couleur spéculaire
    Color specularColor = Color(1.0f, 1.0f, 1.0f) * k_s * specularIntensity;

    // Couleur diffuse
    Color sphereColor = sphere.getColor();
    float diffuseIntensity = std::max(0.0f, normal.computeScalable(lightDir));
    Color diffuseColor = sphereColor * diffuseIntensity;

    // Ajout des couleurs diffuse et spéculaire
    Color newPixel = pixel + diffuseColor + specularColor;

    return newPixel;
  }
  return pixel;
}
