#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "../../include/rayimage/Camera.hpp"
#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/Color.hpp"
#include "../../include/raymath/Light.hpp"
#include "../../include/raymath/Shape.hpp"
#include "../../include/raymath/Vector.hpp"

class Scene {
 private:
  Vector origin;
  Camera camera;
  Light light;
  std::vector<std::unique_ptr<Shape>> shapes;
  Color background;

 public:
  Scene(Vector const& origin, Camera const& camera, Light const& light,
        Color const& background, std::vector<std::unique_ptr<Shape>> shapes);
  ~Scene();

  Vector GetOrigin() const;
  void SetOrigin(Vector const& origin);

  Camera GetCamera() const;
  void SetCamera(Camera camera);

  Light GetLight() const;
  void SetLight(Light const& light);

  Color GetBackground() const;
  void SetBackground(Color background);

  Image rayCast();

  friend std::ostream& operator<<(std::ostream& _stream, Scene const& scene);
};