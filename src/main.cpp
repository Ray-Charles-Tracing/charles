#include <iostream>
#include <vector>

// Include our class definition - we can read it thanks to
// `target_include_directories`
#include <rayimage/Camera.hpp>
#include <rayimage/Image.hpp>
#include <rayimage/Scene.hpp>
#include <raymath/Color.hpp>
#include <raymath/Light.hpp>
#include <raymath/ReflectionType.hpp>
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
  // Create a camera at the origin, looking at the center of the image
  Camera camera(Vector(0, 0, 0), 1.0, image);

  // Create instances of Sphere and add them to a vector
  // Using pointers to take advantage of polymorphism
  std::vector<Shape*> shapes;
  shapes.push_back(
      new Sphere(Vector(0, 0, 0), 1, ReflectionType::DIFFUSE, Color(1, 1, 1)));
  shapes.push_back(
      new Sphere(Vector(2, 2, 0), 1, ReflectionType::SPECULAR, Color(0, 1, 0)));

  // Create a scene with the shapes
  Scene scene(Vector(0, 0, 0), camera, light, black, shapes);

  camera.Render(image);

  // Create a camera at the origin, looking at the center of the image
  Camera camera(Vector(0, 0, 0), 1.0, image);
  camera.Render(image);

  Scene scene(Vector(0, 0, 0), camera, light, black, shapes);

  image.WriteFile("./render/test.png");

  // Test the shapes
  for (Shape* shape : shapes) {
    cout << *shape << endl;
  }

  // Free the dynamically allocated memory
  for (Shape* shape : shapes) {
    delete shape;
  }
}