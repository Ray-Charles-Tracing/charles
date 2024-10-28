#pragma once

#include <iostream>

#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/Vector.hpp"

class Camera {
 private:
  Vector position;
  float fov = 1.0;
  Image image;
  // Shader shader;

 public:
  Camera();
  Camera(Vector position, float fov, Image image);
  ~Camera();

  Vector GetPosition();
  void SetPosition(Vector position);

  float GetFov();
  void SetFov(float fov);

  Image GetImage();
  void SetImage(Image image);

  // Shader GetShader();
  // void SetShader(Shader shader);

  void Render(Image image);

  friend std::ostream& operator<<(std::ostream& _stream, Camera const& camera);
};