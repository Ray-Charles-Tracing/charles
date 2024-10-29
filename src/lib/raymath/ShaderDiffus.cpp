#include "../../include/raymath/ShaderDiffus.hpp"

#include "../../include/raymath/Color.hpp"

Color ShaderDiffus::calculateShader(Color pixel,
                                    std::optional<Vector> intersectionPointOpt,
                                    Ray ray, const Shape& shape,
                                    Light light) const {
  if (intersectionPointOpt.has_value()) {
    Vector intersectionPoint = *intersectionPointOpt;
    Vector vecteur = shape.getPosition();
    Vector cp = intersectionPoint - vecteur;
    Vector normal = cp.normalize();

    Vector pl = light.getPosition() - intersectionPoint;
    Vector lightDir = pl.normalize();

    float intensity = normal.computeScalable(lightDir);

    Color shapeColor = shape.getColor();

    // Utilisation de l'opérateur * pour multiplier l'intensité avec la couleur
    // de la sphère
    Color intensityColor = shapeColor * intensity;

    Color newPixel = pixel + intensityColor;

    return newPixel;
  }
  return pixel;
}
