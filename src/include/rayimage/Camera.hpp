#pragma once

#include <iostream>

#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/ShaderFlat.hpp"  // Shader importé
#include "../../include/raymath/Vector.hpp"

class Camera {
 private:
  Vector position;
  float fov;
  Image image;
  ShaderFlat shader;

 public:
  Camera(Vector position, float fov, Image image, ShaderFlat shader);
  ~Camera();

  Vector GetPosition() const;
  void SetPosition(Vector position);

  float GetFov() const;
  void SetFov(float fov);

  Image& GetImage();
  void SetImage(Image image);

  ShaderFlat GetShader() const;
  void SetShader(ShaderFlat shader);

  void Render(Image renderImage);

  friend std::ostream& operator<<(std::ostream& _stream, Camera const& camera);
};