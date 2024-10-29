#include "../../include/raymath/ShaderDiffus.hpp"

#include "../../include/raymath/Color.hpp"

Color ShaderDiffus::calculateShader(Color pixel,
                                    std::optional<Vector> intersectionPointOpt,
                                    Ray ray, Sphere sphere, Light light) const {
  if (intersectionPointOpt.has_value()) {
    Vector intersectionPoint = *intersectionPointOpt;
    Vector vecteur = sphere.getPosition();
    Vector cp = intersectionPoint - vecteur;
    Vector normal = cp.normalize();

    Vector pl = light.getPosition() - intersectionPoint;
    Vector lightDir = pl.normalize();

    float intensity = normal.computeScalable(lightDir);

    Color sphereColor = sphere.getColor();

    // Utilisation de l'opérateur * pour multiplier l'intensité avec la couleur
    // de la sphère
    Color intensityColor = sphereColor * intensity;

    Color newPixel = pixel + intensityColor;
    /*
        std::cout << "Pixel: " << pixel << std::endl;
        std::cout << "Intensity: " << intensity << std::endl;
        std::cout << "Sphere Color: " << sphereColor << std::endl;
        std::cout << "Intensity Color: " << intensityColor << std::endl;
        std::cout << "New Pixel: " << newPixel << std::endl; */

    return newPixel;
  }
  return pixel;
}
