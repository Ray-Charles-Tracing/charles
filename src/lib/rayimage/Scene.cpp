#include "../../include/rayimage/Scene.hpp"

#include <omp.h>

#include <optional>

#include "../../include/raymath/ShaderFlat.hpp"

Scene::Scene(Vector const& origin, Camera const& camera, Light const& light,
             Color const& background,
             std::vector<std::unique_ptr<Shape>> shapes)
    : origin(origin),
      camera(camera),
      light(light),
      background(background),
      shapes(std::move(shapes)) {}

Scene::~Scene() {}

Vector Scene::GetOrigin() const { return origin; }
void Scene::SetOrigin(Vector const& origin) { this->origin = origin; }

Camera Scene::GetCamera() const { return camera; }
void Scene::SetCamera(Camera camera) { this->camera = camera; }

Light Scene::GetLight() const { return light; }
void Scene::SetLight(Light const& light) { this->light = light; }

Color Scene::GetBackground() const { return background; }
void Scene::SetBackground(Color background) { this->background = background; }

Image Scene::rayCast() {
  std::cout << "Executing ray casting..." << std::endl;

  // Access class members directly to avoid repetitive method calls
  Image& image = camera.GetImage();
  int width = image.GetWidth();
  int height = image.GetHeight();
  ShaderFlat shaderFlat = camera.GetShader();
  Vector cameraPosition = camera.GetPosition();

  float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
  float coordonateXIncrement = 2.0 * aspectRatio / width;
  float coordonateYIncrement = 2.0 / height;

// Parallelize the nested loops
// `#pragma omp parallel for collapse(2)` creates a parallel region and
// distributes the iterations of the nested loops among the threads. The
// `collapse(2)` clause combines the two loops into a single loop for better
// load balancing.
#pragma omp parallel for collapse(2)
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float coordonateX = -1.0 * aspectRatio + x * coordonateXIncrement;
      float coordonateY = 1.0 - y * coordonateYIncrement;

      Ray ray(cameraPosition, Vector(coordonateX, coordonateY, 1));
      Color pixelColor = background;

      // Use local variables to avoid repetitive dynamic casts
      for (const auto& shape : shapes) {
        // `std::optional` is used to represent optional values that may or may
        // not be present. It is used here to handle the case where there is no
        // intersection point.
        std::optional<Vector> intersectPointOpt = shape->getIntersectPoint(ray);
        if (intersectPointOpt.has_value()) {
          Vector intersectPoint = intersectPointOpt.value();
          pixelColor =
              shaderFlat.calculateShader(pixelColor, intersectPointOpt, ray,
                                         *dynamic_cast<Sphere*>(shape.get()));
          // Exit the loop once an intersection is found
          // This avoids unnecessary calculations for the remaining shapes
          break;
        }
      }

      image.SetPixel(x, y, pixelColor);
    }
  }

  std::cout << "Ray casting completed." << std::endl;
  return image;
}

std::ostream& operator<<(std::ostream& _stream, const Scene& scene) {
  _stream << "Origin: " << scene.origin << ", Camera: " << scene.camera
          << ", Light: " << scene.light << ", Background: " << scene.background;
  return _stream;
}