#pragma once

#include <iostream>

#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/ShaderPhong.hpp"
#include "../../include/raymath/Vector.hpp"

class Camera {
 private:
  Vector position;
  float fov;
  Image image;
  ShaderPhong shader;

 public:
  Camera(Vector position, float fov, Image image, ShaderPhong shader);
  ~Camera();

  Vector GetPosition() const;
  void SetPosition(Vector position);

  float GetFov() const;
  void SetFov(float fov);

  Image& GetImage();
  void SetImage(Image image);

  ShaderPhong GetShader() const;
  void SetShader(ShaderPhong shader);

  void Render(Image renderImage);

  friend std::ostream& operator<<(std::ostream& _stream, Camera const& camera);
};