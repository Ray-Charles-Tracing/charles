#pragma once

#include <iostream>
#include <vector>

#include "../../include/rayimage/Camera.hpp"
#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/Color.hpp"
#include "../../include/raymath/Light.hpp"
#include "../../include/raymath/Sphere.hpp"
#include "../../include/raymath/Vector.hpp"

class Scene {
 private:
  Vector origin;
  Camera camera;
  std::vector<Light> lights;
  Color background;
  std::vector<Sphere> spheres;

 public:
  Scene(Vector const& origin, Camera const& camera, std::vector<Light> lights,
        Color const& background, std::vector<Sphere> spheres);
  ~Scene();

  Vector GetOrigin() const;
  void SetOrigin(Vector const& origin);

  Camera GetCamera() const;
  void SetCamera(Camera camera);

  std::vector<Light> GetLights() const;
  void SetLights(std::vector<Light> lights);

  Color GetBackground() const;
  void SetBackground(Color background);

  Image rayCast(int maxReflections = 3);

  Color traceRay(const Ray& ray, int depth);

  bool isPointInShadow(const Vector& point, const Light& light) const;

  friend std::ostream& operator<<(std::ostream& _stream, Scene const& scene);
};