#include "../../include/rayimage/Camera.hpp"

Camera::Camera(Vector position, float fov, Image image)
    : position(position), fov(fov), image(image) {
  std::cout << "Creating camera..." << std::endl;
}

void Camera::Render(Image image) {
  std::cout << "Rendering image..." << std::endl;
  image.WriteFile("./render/test.png");
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

// Shader Camera::GetShader() { return this->shader; }
// void Camera::SetShader(Shader shader) { this->shader = shader; }

std::ostream& operator<<(std::ostream& _stream, Camera const& camera) {
  _stream << "Camera: {" << std::endl;
  _stream << "  Position: " << camera.position << std::endl;
  _stream << "  FOV: " << camera.fov << std::endl;
  // _stream << "  Image: " << camera.image << std::endl;

  _stream << "}";
  return _stream;
}