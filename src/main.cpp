#include <iostream>

// Include our class definition - we can read it thanks to
// `target_include_directories`
#include <rayimage/Image.hpp>
#include <raymath/Color.hpp>
#include <raymath/Light.hpp>
#include <raymath/Ray.hpp>
#include <raymath/ReflectionType.hpp>
#include <raymath/Shader.hpp>
#include <raymath/ShaderFlat.hpp>
#include <raymath/Shape.hpp>
#include <raymath/Sphere.hpp>
#include <raymath/Vector.hpp>

using namespace std;

int main() {
  Color red(1, 0, 0);
  Color redLowIntensity = red * 0.24;
  Color green(0, 1, 0);
  Color black;

  cout << "Red : " << red << std::endl;
  cout << "Red low intensity : " << redLowIntensity << std::endl;
  cout << "Green : " << green << std::endl;
  cout << "Black : " << black << std::endl;

  Color yellow = red + green;

  cout << "Yellow : " << yellow << std::endl;

  // Create an image in memory, and fill it with yellow
  Image image(512, 512, yellow);

  // Create a light source
  Light light(Color(1, 1, 1),
              Vector(256, 256, 0));  // White light at the center of the image

  cout << "Light: " << light << std::endl;

  // Make a red square on the top left of the image
  for (int y = 0; y < 100; y++) {
    for (int x = 0; x < 100; x++) {
      image.SetPixel(x, y, redLowIntensity);
    }
  }

  image.WriteFile("./render/test.png");

  // ! This is sphere test
  Sphere sphere(Vector(0, 0, 0), 1, ReflectionType::DIFFUSE, Color(1, 0.5, 1));
  cout << sphere << endl;

  Ray ray(Vector(0, 0, 0), Vector(1, 1, 1));
  cout << "Ray origin: " << ray.getOrigin() << std::endl;
  cout << "Ray direction: " << ray.getDirection() << std::endl;

  // Create a Shader
  ShaderFlat shaderFlat;
  cout << shaderFlat.calculateShader(
              Color(0, 0, 0), Ray(Vector(0, 0, 0), Vector(7, 8, 9)), sphere)
       << endl;

}
