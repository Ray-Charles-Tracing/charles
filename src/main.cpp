#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

// Include our class definition - we can read it thanks to
// `target_include_directories`
#include "rayimage/Camera.hpp"
#include "rayimage/Image.hpp"
#include "rayimage/Scene.hpp"
#include "raymath/Color.hpp"
#include "raymath/Light.hpp"
#include "raymath/Ray.hpp"
#include "raymath/ReflectionType.hpp"
#include "raymath/ShaderFlat.hpp"
#include "raymath/Shape.hpp"
#include "raymath/Sphere.hpp"
#include "raymath/Vector.hpp"

using namespace std;

int main() {
  // Ensure the output directory exists
  std::filesystem::create_directories("./render");

  // Initialize colors
  Color red(1, 0, 0);
  Color black;

  // Initialize the image
  int width = 1920;
  int height = 1920;
  Image image(width, height);

  // Initialize the light
  Light light(Color(1, 1, 1), Vector(256, 256, 0));

  // Initialize the shader
  ShaderFlat shaderFlat;

  // Initialize the camera
  Camera camera(Vector(0, 0, 0), 1.0, image, shaderFlat);

  // Initialize shapes
  // Using std::unique_ptr to manage the memory of shapes automatically
  // This ensures that the shapes are properly deleted when they go out of scope
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Sphere>(
      Vector(6, -6, 45), 6, ReflectionType::MAT, Color(0, 1, 1)));

  // Initialize the scene
  Scene scene(Vector(0, 0, 0), camera, light, black, std::move(shapes));

  // Execute raycasting and render the image
  Image renderImage = scene.rayCast();
  camera.Render(renderImage);

  return 0;
}