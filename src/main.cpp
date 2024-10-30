#include <cmath>
#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

// Include our class definition - we can read it thanks to
// `target_include_directories`
#include <rayimage/Camera.hpp>
#include <rayimage/Image.hpp>
#include <rayimage/Scene.hpp>
#include <raymath/Color.hpp>
#include <raymath/Light.hpp>
#include <raymath/MaterialType.hpp>
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
  // Ensure the output directory exists
  std::filesystem::create_directories("./render");

  // Initialize colors
  Color red(1, 0, 0);
  Color black;

  // Create an image in memory
  int width = 1920;
  int height = 1920;
  Image image(width, height);

  // Create light sources
  vector<Light> lights = {
      Light(Color(1, 1, 1), Vector(0, 0, 0))
      /* Light(Color(0, 1, 1), Vector(128, 128, 128)),
      Light(Color(1, 1, 0), Vector(-128, -128, 128)),
      Light(Color(1, 0, 1), Vector(-128, 128, 128)), */
      // Light(Color(1, 1, 1), Vector(0, 45, 0))
  };

  // Liste des sphères
  std::vector<std::unique_ptr<Shape>> shapes;

  shapes.push_back(std::make_unique<Sphere>(
      Vector(-15, 0, 20), 3, ReflectionType::REFLECTIVE, Color(0, 1, 1),
      MaterialType::WOOD));
  shapes.push_back(
      std::make_unique<Sphere>(Vector(-5, 0, 20), 3, ReflectionType::REFLECTIVE,
                               Color(0, 1, 1), MaterialType::PLASTIC));
  shapes.push_back(
      std::make_unique<Sphere>(Vector(5, 0, 20), 3, ReflectionType::REFLECTIVE,
                               Color(0, 1, 1), MaterialType::METAL));
  shapes.push_back(
      std::make_unique<Sphere>(Vector(15, 0, 20), 3, ReflectionType::REFLECTIVE,
                               Color(0, 1, 1), MaterialType::CERAMIC));

  // Create a shared pointer to the shader
  std::shared_ptr<Shader> shader = std::make_shared<ShaderPhong>();

  // Initialize the camera
  Camera camera(Vector(0, 0, 0), 1.0, image, shader);

  // Initialize the scene
  Scene scene(Vector(0, 0, 0), camera, std::move(lights), black,
              std::move(shapes));

  // Execute raycasting and render the image
  Image renderImage = scene.rayCast();
  camera.Render(renderImage);

  return 0;
}