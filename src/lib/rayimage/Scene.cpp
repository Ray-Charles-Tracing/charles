#include "../../include/rayimage/Scene.hpp"

#include <omp.h>

#include <limits>  // Include the limits header for std::numeric_limits
#include <optional>

#include "../../include/raymath/ShaderPhong.hpp"

Scene::Scene(Vector const& origin, Camera const& camera,
             std::vector<Light> lights, Color const& background,
             std::vector<std::unique_ptr<Shape>>&& shapes)
    : origin(origin),
      camera(camera),
      lights(std::move(lights)),
      background(background),
      shapes(std::move(shapes)) {}

Scene::~Scene() {}

Vector Scene::GetOrigin() const { return origin; }
void Scene::SetOrigin(Vector const& origin) { this->origin = origin; }

Camera Scene::GetCamera() const { return camera; }
void Scene::SetCamera(Camera camera) { this->camera = camera; }

std::vector<Light> Scene::GetLights() const { return lights; }
void Scene::SetLights(std::vector<Light> lights) {
  this->lights = std::move(lights);
}

Color Scene::GetBackground() const { return background; }
void Scene::SetBackground(Color background) { this->background = background; }

Image Scene::rayCast(int maxReflections) {
  std::cout << "Executing ray casting..." << std::endl;

  // Access class members directly to avoid repetitive method calls
  Image& image = camera.GetImage();
  int width = image.GetWidth();
  int height = image.GetHeight();
  std::shared_ptr<Shader> shader = camera.GetShader();
  Vector cameraPosition = camera.GetPosition();

  float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
  float coordonateXIncrement = 1.0 * aspectRatio / width;
  float coordonateYIncrement = 1.0 / height;

  // Parallelize the nested loops
  // `#pragma omp parallel for collapse(2)` creates a parallel region and
  // distributes the iterations of the nested loops among the threads. The
  // `collapse(2)` clause combines the two loops into a single loop for better
  // load balancing.
#pragma omp parallel for collapse(2)
  float coordonateY = 0.5;
  for (int y = 0; y < height; y++) {
    float coordonateX = -0.5 * aspectRatio;
    for (int x = 0; x < width; x++) {
      Ray ray(cameraPosition, Vector(coordonateX, coordonateY, 1));
      Color pixelColor = traceRay(ray, maxReflections);

      image.SetPixel(x, y, pixelColor);
      coordonateX += coordonateXIncrement;
    }
    coordonateY -= coordonateYIncrement;
  }

  std::cout << "Ray casting completed." << std::endl;
  return image;
}

Color Scene::traceRay(const Ray& ray, int depth) {
  if (depth <= 0) {
    return background;
  }

  float closestDistance = std::numeric_limits<float>::max();
  std::optional<Vector> closestIntersectPoint;
  Shape* closestShape = nullptr;

  for (auto& shape : shapes) {
    // `std::optional` is used to represent optional values that may or may
    // not be present. It is used here to handle the case where there is no
    // intersection point.
    std::optional<Vector> intersectPointOpt = shape->getIntersectPoint(ray);
    float distance = intersectPointOpt.has_value()
                         ? (ray.getOrigin() - *intersectPointOpt).getNorm()
                         : std::numeric_limits<float>::max();

    if (distance < closestDistance) {
      closestDistance = distance;
      closestIntersectPoint = intersectPointOpt;
      closestShape = shape.get();  // Get the raw pointer from the unique_ptr
    }
  }

  if (closestShape && closestIntersectPoint.has_value()) {
    Color pixelColor = background;
    std::shared_ptr<Shader> shader =
        camera.GetShader();  // Ensure shader is accessible
    for (const auto& light : lights) {
      pixelColor += shader->calculateShader(pixelColor, closestIntersectPoint,
                                            ray, *closestShape, light);
    }

    // Handle reflection
    if (closestShape->getReflectionType() == ReflectionType::REFLECTIVE) {
      Vector intersectionPoint = *closestIntersectPoint;
      Vector normal =
          (intersectionPoint - closestShape->getPosition()).normalize();
      Vector reflectionDirection =
          ray.getDirection() -
          normal * 2 * ray.getDirection().computeScalable(normal);
      Ray reflectionRay(intersectionPoint, reflectionDirection);

      Color reflectionColor = traceRay(reflectionRay, depth - 1);
      pixelColor += reflectionColor * 0.5;  // Adjust reflection intensity
    }

    return pixelColor;
  }

  return background;
}

std::ostream& operator<<(std::ostream& _stream, const Scene& scene) {
  _stream << "Origin: " << scene.origin << ", Camera: " << scene.camera
          << ", Lights: [";
  for (const auto& light : scene.lights) {
    _stream << light << ", ";
  }
  _stream << "], Background: " << scene.background;
  return _stream;
}