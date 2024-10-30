#include "../../include/raymath/ShaderPhong.hpp"

#include <cmath>

// Fonction pour vérifier si un point est visible depuis la lumière
bool isPointVisibleFromLight(
    const Vector& point, const Light& light,
    const std::vector<std::unique_ptr<Shape>>& objects) {
  Vector lightDir = (light.getPosition() - point).normalize();
  Vector shadowOrigin =
      point +
      lightDir * 1e-4f;  // Décalage pour éviter les erreurs de précision
  Ray shadowRay(shadowOrigin, lightDir);  // Crée un rayon vers la lumière

  for (const auto& object : objects) {
    std::optional<Vector> intersectPointOpt =
        object->getIntersectPoint(shadowRay);
    if (intersectPointOpt.has_value()) {
      float distanceToIntersect = (shadowOrigin - *intersectPointOpt).getNorm();
      float distanceToLight = (light.getPosition() - point).getNorm();

      if (distanceToIntersect < distanceToLight) {
        return false;  // Un objet bloque la lumière
      }
    }
  }
  return true;  // Pas d'obstacle, la lumière atteint le point
}

Color ShaderPhong::calculateShader(
    Color pixel, std::optional<Vector> intersectionPointOpt, Ray ray,
    const Shape& shape, Light light,
    const std::vector<std::unique_ptr<Shape>>& objects) const {
  if (intersectionPointOpt.has_value()) {
    Color shapeColor = shape.getColor();
    Color lightColor = light.getColor();
    float k_d = shape.getDiffuseReflexionCoef();

    // Vérifier si le point est dans l'ombre pour cette lumière
    if (!isPointVisibleFromLight(*intersectionPointOpt, light, objects)) {
      return pixel;  // Le point est dans l'ombre, pas de contribution de cette
                     // lumière
    }

    // Obtenir les bases pour le calcul de l'éclairage diffus et spéculaire
    Vector intersectionPoint, normal, lightDir, viewDir;
    std::tie(intersectionPoint, normal, lightDir, viewDir) =
        this->getDiffuseBases(*intersectionPointOpt, ray, shape, light);

    float diffuseIntensity;
    Color specularColor;
    std::tie(diffuseIntensity, specularColor) = this->getSpeculareBases(
        lightDir, normal, shape, viewDir, lightColor, light);

    // Ajuster l'intensité spéculaire en fonction de la rugosité
    float adjustedSpecularIntensity = specularColor.R();
    for (int i = 0; i < static_cast<int>(shape.getRoughness() * 10); ++i) {
      adjustedSpecularIntensity *= specularColor.R();
    }
    specularColor = Color(1.0f, 1.0f, 1.0f) * shape.getSpecularReflexionCoef() *
                    adjustedSpecularIntensity;

    // Calcul de la couleur diffuse
    Color diffuseColor = shapeColor * k_d * diffuseIntensity * lightColor;

    // Couleur finale
    Color newPixel = pixel + diffuseColor + specularColor;

    // Normaliser la couleur finale pour éviter des valeurs supérieures à 1
    newPixel = Color(std::min(newPixel.R(), 1.0f), std::min(newPixel.G(), 1.0f),
                     std::min(newPixel.B(), 1.0f));

    return newPixel;
  }
  return pixel;
}
