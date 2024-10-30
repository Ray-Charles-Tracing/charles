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
#include <rayimage/Image.hpp>
#include <rayimage/Scene.hpp>
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
  // Ensure the output directory exists
  std::filesystem::create_directories("./render");

  // Initialize colors
  Color red(1, 0, 0);
  Color green(0, 1, 0);
  Color blue(0, 0, 1);
  Color black;

  // Create an image in memory
  int width = 800;
  int height = 800;
  Image image(width, height);

  // Create light sources
  vector<Light> lights = {Light(Color(1, 1, 1), Vector(0, 0, 0))};

  // List of shapes
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Sphere>(
      Vector(0, 0, 20), 5, ReflectionType::REFLECTIVE, Color(1, 1, 0)));
  shapes.push_back(std::make_unique<Sphere>(
      Vector(14, 0, 20), 5, ReflectionType::REFLECTIVE, Color(0, 1, 1)));
  shapes.push_back(std::make_unique<Sphere>(
      Vector(-14, 0, 20), 5, ReflectionType::REFLECTIVE, Color(1, 0, 0)));
  // Create a shared pointer to the shader
  std::shared_ptr<Shader> shader = std::make_shared<ShaderPhong>();

  // Initialize the camera
  Camera camera(Vector(0, 0, 0), 1.0, image, shader);

  // Initialize the scene
  Scene scene(Vector(0, 0, 0), camera, std::move(lights), black,
              std::move(shapes));

  // Start the timer for rendering
  auto start = std::chrono::high_resolution_clock::now();

  // Execute raycasting and render the image
  Image renderImage = scene.rayCast(3);  // Set max reflections to 3
  camera.Render(renderImage);

  // Stop the timer for rendering
  auto end = std::chrono::high_resolution_clock::now();

  // Calculate the duration
  std::chrono::duration<double> duration = end - start;

  // Print the duration
  std::cout << "Rendering time: " << duration.count() << " seconds"
            << std::endl;

  return 0;
}