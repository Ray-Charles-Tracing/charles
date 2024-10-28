#include "../raymath/Vector.hpp"
#include "Shape.hpp"

class Sphere : public Shape {
 private:
  float radius;

 public:
  Sphere(Vector position, float radius);
  Sphere(Vector position, float scale, float radius);
  ~Sphere() = default;

  Vector intersect(Vector ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere);
};