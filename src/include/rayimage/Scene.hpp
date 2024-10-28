#include "rayimage/Camera.hpp"
#include "raymath/Color.hpp"
#include "raymath/Vector.hpp"

class Scene {
 private:
  origin : Vector;
  camera : Camera;
  light : Light;
  shapes : Shapes[];
  background : Color;

 public:
  Scene(Vector origin, Camera camera, Color background);
  ~Scene();

  void AddShape(Shape shape);

  void AddLight(Light light);

  Vector GetOrigin();
  void SetOrigin(Vector origin);

  Camera GetCamera();
  void SetCamera(Camera camera);

  Color GetBackground();
  void SetBackground(Color background);
}