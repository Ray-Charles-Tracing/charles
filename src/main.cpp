#include <cmath>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

// Inclusion de nos définitions de classe
#include <rayimage/Image.hpp>
#include <raymath/Color.hpp>
#include <raymath/Light.hpp>
#include <raymath/Ray.hpp>
#include <raymath/ReflectionType.hpp>
#include <raymath/Shader.hpp>
#include <raymath/ShaderDiffus.hpp>
#include <raymath/ShaderFlat.hpp>
#include <raymath/ShaderPecular.hpp>
#include <raymath/ShaderPhong.hpp>
#include <raymath/Shape.hpp>
#include <raymath/Sphere.hpp>
#include <raymath/Vector.hpp>

using namespace std;

int main() {
  Color red(1, 0, 0);
  Color green(0, 1, 0);
  Color black;

  // Création d'une image en mémoire
  int width = 1920;
  int height = 1920;
  Image image(width, height);

  // Création des sources de lumière
  vector<Light> lights = {Light(Color(0, 1, 1), Vector(128, 128, 128)),
                          Light(Color(1, 1, 0), Vector(-128, -128, 128)),
                          Light(Color(1, 0, 1), Vector(-128, 128, 128))/* , 
                          Light(Color(1, 1, 1), Vector(0, 45, 0)) */};

  // Liste des sphères
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Sphere>(
      Vector(-4, 4, 25), 3, ReflectionType::MAT, Color(1, 1, 0)));
  shapes.push_back(std::make_unique<Sphere>(
      Vector(6, -6, 45), 6, ReflectionType::MAT, Color(0, 1, 1)));
  shapes.push_back(std::make_unique<Sphere>(
      Vector(4, -4, 15), 4, ReflectionType::MAT, Color(1, 0, 0)));

  ShaderPhong shaderPhong;

  // Calculate aspect ratio
  float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

  // Make a red square on the top left of the image
  /*   float coordonateY = 1.0;
   */
  // Remplissage de l'image
  for (int y = 0; y < height; y++) {
    /*     float coordonateX = -1.0 * aspectRatio;
     */
    for (int x = 0; x < width; x++) {
      float coordonateX = (x - width / 2.0f) / (width / 2.0f);
      float coordonateY = (y - height / 2.0f) / (height / 2.0f);
      Ray ray(Vector(0, 0, 0), Vector(coordonateX, coordonateY, 1));

      float closestDistance = numeric_limits<float>::max();
      Color pixelColorPhong;
      optional<Vector> closestIntersectPoint;
      Shape* closestShape = nullptr;

      for (auto& shape : shapes) {  // Trier spheres par ordre de profondeur,
                                    // la plus proche en premier
        optional<Vector> intersectPointOpt = shape->getIntersectPoint(ray);
        float distance = intersectPointOpt.has_value()
                             ? (ray.getOrigin() - *intersectPointOpt).getNorm()
                             : numeric_limits<float>::max();

        if (distance < closestDistance) {
          closestDistance = distance;
          closestIntersectPoint = intersectPointOpt;
          closestShape = shape.get();
        }
      }

      if (closestShape) {
        for (const auto& light : lights) {
          if (closestIntersectPoint.has_value()) {
            pixelColorPhong += shaderPhong.calculateShader(
                Color(0, 0, 0), closestIntersectPoint, ray, *closestShape,
                light);
          }
        }
      }

      // Définir la couleur du pixel
      image.SetPixel(x, y, pixelColorPhong);

/*       coordonateX += 2.0 * aspectRatio / width;
 */    }
/*  coordonateY -= 2.0 / height; */
  }

  // Écriture de l'image dans un fichier
  image.WriteFile("./render/test.png");
}
