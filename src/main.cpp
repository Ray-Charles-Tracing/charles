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

  // Shapes and lights
  vector<Light> lights = config.getLights();
  std::vector<std::unique_ptr<Shape>> shapes = config.getShapes();

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