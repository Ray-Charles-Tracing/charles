#pragma once

#include <iostream>

#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/Vector.hpp"

class Camera {
 private:
  position : Vector;
  fov : float;
  image : Image;
  // shader: Shader;

 public:
  Camera(Vector position, float fov, Image image);
  ~Camera();

  void SetPosition(Vector position);
  void SetFov(float fov);
  void SetImage(Image image);
  // void SetShader(Shader shader);

  Vector GetPosition();
  float GetFov();
  Image GetImage();
  // Shader GetShader();

  void Render();
};