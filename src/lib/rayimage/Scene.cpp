#include "../../include/rayimage/Scene.hpp"

#include <iostream>
#include <vector>

Scene::Scene(Vector const& origin, Camera const& camera, Light const& light,
             Color const& background)
    : origin(origin), camera(camera), background(background) {}

Scene::~Scene() {
  std::cout << "Destroying scene..." << std::endl;
  return;
}

Vector Scene::GetOrigin() const { return this->origin; }
void Scene::SetOrigin(Vector const& origin) { this->origin = origin; }

Camera Scene::GetCamera() { return this->camera; }
void Scene::SetCamera(Camera camera) { this->camera = camera; }

Color Scene::GetBackground() { return this->background; }
void Scene::SetBackground(Color background) { this->background = background; }

std::ostream& operator<<(std::ostream& _stream, Scene const& scene) {
  _stream << "Scene: {" << std::endl;
  _stream << "  Origin: " << scene.origin << std::endl;
  _stream << "  Background: " << scene.background << std::endl;
  // _stream << "  Camera: " << scene.camera << std::endl;
  _stream << "}";
  return _stream;
}