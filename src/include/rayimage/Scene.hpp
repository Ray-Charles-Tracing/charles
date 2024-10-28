#pragma once

#include <iostream>
#include <vector>

#include "../../include/rayimage/Camera.hpp"
#include "../../include/raymath/Color.hpp"
#include "../../include/raymath/Light.hpp"
#include "../../include/raymath/Shape.hpp"
#include "../../include/raymath/Vector.hpp"

class Scene {
 private:
  Vector origin;
  Camera camera;
  Light light;
  std::vector<Shape*> shapes;  // Tableau de pointeurs vers Shape
  Color background;

 public:
  Scene(Vector const& origin, Camera const& camera, Light const& light,
        Color const& background, std::vector<Shape*> const& shapes);
  ~Scene();

  Vector GetOrigin() const;
  void SetOrigin(Vector const& origin);

  Camera GetCamera();
  void SetCamera(Camera camera);

  Light GetLight() const;
  void SetLight(Light const& light);

  Color GetBackground();
  void SetBackground(Color background);

  friend std::ostream& operator<<(std::ostream& _stream, Scene const& scene);
};