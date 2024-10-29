#pragma once

#include <iostream>
#include <memory>

#include "../../include/rayimage/Image.hpp"
#include "../../include/raymath/Shader.hpp"
#include "../../include/raymath/Vector.hpp"

class Camera {
 private:
  Vector position;
  float fov;
  Image image;
  std::shared_ptr<Shader> shader;  // Use shared_ptr to manage the shader

 public:
  Camera(Vector position, float fov, Image image,
         std::shared_ptr<Shader> shader);
  ~Camera();

  Vector GetPosition() const;
  void SetPosition(Vector position);

  float GetFov() const;
  void SetFov(float fov);

  Image& GetImage();
  void SetImage(Image image);

  std::shared_ptr<Shader> GetShader() const;
  void SetShader(std::shared_ptr<Shader> shader);

  void Render(Image renderImage);

  friend std::ostream& operator<<(std::ostream& _stream, Camera const& camera);
};