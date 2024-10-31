#include <chrono>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

// Include our class definition - we can read it thanks to
// `target_include_directories`
#include <rayimage/Camera.hpp>
#include <rayimage/Config.hpp>
#include <rayimage/Image.hpp>
#include <rayimage/Scene.hpp>
#include <raymath/Color.hpp>
#include <raymath/Light.hpp>
#include <raymath/MaterialType.hpp>
#include <raymath/Plan.hpp>
#include <raymath/Ray.hpp>
#include <raymath/ReflectionType.hpp>
#include <raymath/Shader.hpp>
#include <raymath/ShaderDiffus.hpp>
#include <raymath/ShaderFlat.hpp>
#include <raymath/ShaderPecular.hpp>
#include <raymath/ShaderPhong.hpp>
#include <raymath/Shape.hpp>
#include <raymath/Sphere.hpp>
#include <raymath/Triangle.hpp>
#include <raymath/Vector.hpp>

using namespace std;

int main() {
  // Load the configuration
  Config config("config.json");
  if (!config.loadConfig()) {
    return 1;
  }

  // Ensure the output directory exists
  std::string output_directory = config.getOutputDirectory();
  std::filesystem::create_directories(output_directory);

  // Create an image in memory
  int width = config.getImageWidth();
  int height = config.getImageHeight();
  Image image(width, height);

  // Create light sources
  //   vector<Light> lights = config.getLights();
  vector<Light> lights = {//   Light(Color(0, 1, 1), Vector(128, 128, 128)),
                          //   Light(Color(1, 1, 0), Vector(-128, -128, 128)),
                          //   Light(Color(1, 0, 1), Vector(-128, 128, 128)),
                          // Light(Color(1, 1, 1), Vector(0, 45, 0))
                          Light(Color(1, 1, 1), Vector(-10, 10, 0)),
                          Light(Color(1, 1, 1), Vector(10, 10, 0))};

  // List of shapes
  //   std::vector<std::unique_ptr<Shape>> shapes = config.getShapes();
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Plan>(
      Vector(0, -5, 0), Vector(0, 1, 0), ReflectionType::REFLECTIVE,
      Color(0.7, 0.7, 0.7), MaterialType::METAL));
  shapes.push_back(std::make_unique<Sphere>(
      Vector(-15, 0, 20), 3, ReflectionType::REFLECTIVE, Color(0, 1, 1),
      MaterialType::WOOD));
  shapes.push_back(std::make_unique<Sphere>(Vector(-5, 0, 20), 3,
                                            ReflectionType::MAT, Color(0, 1, 1),
                                            MaterialType::PLASTIC));
  shapes.push_back(
      std::make_unique<Sphere>(Vector(5, 0, 20), 3, ReflectionType::REFLECTIVE,
                               Color(0, 1, 1), MaterialType::METAL));
  shapes.push_back(
      std::make_unique<Sphere>(Vector(15, 0, 20), 3, ReflectionType::REFLECTIVE,
                               Color(0, 1, 1), MaterialType::CERAMIC));
  shapes.push_back(std::make_unique<Triangle>(
      Vector(-15, -4, 25), Vector(0, 15, 25), Vector(15, -4, 25),
      ReflectionType::REFLECTIVE, Color(0, 0, 1), MaterialType::METAL));

  // Create a shared pointer to the shader
  std::shared_ptr<Shader> shader = config.getShader();

  // Initialize the camera
  Camera camera(Vector(0, 0, 0), 1.0, image, shader);

  // Initialize the scene
  Color background = config.getBackgroundColor();
  Scene scene(Vector(0, 0, 0), camera, std::move(lights), background,
              std::move(shapes));

  // Start the timer for rendering
  auto start = std::chrono::high_resolution_clock::now();

  // Execute raycasting and render the image
  Image renderImage =
      scene.rayCast(config.getMaxReflections());  // Set max reflections
  camera.Render(renderImage);

  // End the timer for rendering & print the duration
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Rendering time: " << duration.count() << " seconds"
            << std::endl;

  return 0;
}