#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <rayimage/Camera.hpp>
#include <rayimage/Config.hpp>
#include <rayimage/Image.hpp>
#include <rayimage/Scene.hpp>
#include <raymath/Color.hpp>
#include <raymath/Light.hpp>
#include <raymath/Vector.hpp>
#include <vector>

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
  vector<Light> lights = config.getLights();

  // List of shapes
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

  // Export the scene to an OBJ file
  scene.exportToObj("./render/scene.obj");

  // Export the scene to an OBJ file
  scene.exportToObj("./render/scene.obj");

  // End the timer for rendering & print the duration
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Rendering time: " << duration.count() << " seconds"
            << std::endl;

  return 0;
}