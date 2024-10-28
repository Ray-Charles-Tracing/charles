#include "../../include/raymath/Scene.hpp"

Scene::Scene(Vector origin, Camera camera, Color background)
    : origin(origin), camera(camera), background(background) {
  this->origin = origin;
  this->camera = camera;
  this->background = background;
}

Scene::~Scene() {
  std::cout << "Destroying scene..." << std::endl;
  return;
}

void Scene::AddShape(Shape shape) { this->shapes.push_back(shape); }

void Scene::AddLight(Light light) { this->lights.push_back(light); }

Vector Scene::GetOrigin() { return this->origin; }
void Scene::SetOrigin(Vector origin) { this->origin = origin; }

Camera Scene::GetCamera() { return this->camera; }
void Scene::SetCamera(Camera camera) { this->camera = camera; }

Color Scene::GetBackground() { return this->background; }
void Scene::SetBackground(Color background) { this->background = background; }