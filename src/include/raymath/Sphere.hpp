#include "Material.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Sphere : public Shape, Material {
 private:
  float radius;

 public:
  Sphere(Vector position, float radius, ReflectionType reflectionType,
         Color color);
  Sphere(Vector position, float scale, float radius,
         ReflectionType reflectionType, Color color);
  ~Sphere() = default;

  Vector intersect(Vector ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere);
};