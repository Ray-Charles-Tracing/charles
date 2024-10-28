#include "../../include/rayimage/Camera.hpp"

#include "Camera.hpp"

Camera::Camera(Vector position, float fov, Image image)
    : position(position), fov(fov), image(image) {
  this->position = position;
  this->fov = fov;
  this->image = image;
}

void Camera::Render() {
  std::cout << "Rendering image..." << std::endl;
  return;
}

Camera::~Camera() {
  std::cout << "Destroying camera..." << std::endl;
  return;
}

Image Camera::GetImage() { return this->image; }
void Camera::SetImage(Image image) { this->image = image; }

Vector Camera::GetPosition() { return this->position; }
void Camera::SetPosition(Vector position) { this->position = position; }

float Camera::GetFov() { return this->fov; }
void Camera::SetFov(float fov) { this->fov = fov; }

Shader Camera::GetShader() { return this->shader; }
void Camera::SetShader(Shader shader) { this->shader = shader; }
