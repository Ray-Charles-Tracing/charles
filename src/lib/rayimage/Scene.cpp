#include "../../include/rayimage/Scene.hpp"

Scene::Scene(Vector const& origin, Camera const& camera, Light const& light,
             Color const& background, std::vector<Shape*> const& shapes)
    : origin(origin),
      camera(camera),
      light(light),
      background(background),
      shapes(shapes) {}

Scene::~Scene() {
  // Supprime toutes les formes pour éviter les fuites de mémoire
  for (Shape* shape : shapes) {
    delete shape;
  }
}

Vector Scene::GetOrigin() const { return origin; }
void Scene::SetOrigin(Vector const& origin) { this->origin = origin; }

Camera Scene::GetCamera() { return camera; }
void Scene::SetCamera(Camera camera) { this->camera = camera; }

Light Scene::GetLight() const { return light; }
void Scene::SetLight(Light const& light) { this->light = light; }

Color Scene::GetBackground() { return background; }
void Scene::SetBackground(Color background) { this->background = background; }

std::ostream& operator<<(std::ostream& _stream, Scene const& scene) {
  _stream << "Origin: " << scene.origin << ", Camera: " << scene.camera
          << ", Light: " << scene.light << ", Background: " << scene.background;
  return _stream;
}