#include "../../include/rayimage/Camera.hpp"

Camera::Camera(Vector position, float fov, Image image,
               std::shared_ptr<Shader> shader)
    : position(position), fov(fov), image(image), shader(shader) {
  std::cout << "Creating camera..." << std::endl;
}

Camera::~Camera() {}

Vector Camera::GetPosition() const { return position; }
void Camera::SetPosition(Vector position) { this->position = position; }

float Camera::GetFov() const { return fov; }
void Camera::SetFov(float fov) { this->fov = fov; }

Image& Camera::GetImage() { return image; }
void Camera::SetImage(Image image) { this->image = image; }

std::shared_ptr<Shader> Camera::GetShader() const { return shader; }
void Camera::SetShader(std::shared_ptr<Shader> shader) {
  this->shader = shader;
}

void Camera::Render(Image renderImage) {
  std::cout << "Rendering image..." << std::endl;
  renderImage.WriteFile("./render/cameraRender2.png");
}

std::ostream& operator<<(std::ostream& _stream, Camera const& camera) {
  _stream << "Camera: {" << std::endl;
  _stream << "  Position: " << camera.position << std::endl;
  _stream << "  FOV: " << camera.fov << std::endl;
  _stream << "}";
  return _stream;
}