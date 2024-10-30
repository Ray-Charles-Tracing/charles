#pragma once

#include <iostream>
#include <optional>

#include "Material.hpp"
#include "MaterialType.hpp"  // Include the MaterialType header
#include "Vector.hpp"

class Shape : public Material {
 protected:
  Vector position;
  MaterialType materialType;
  float scale;
  virtual bool isVisible(Ray ray, Vector cameraShapeDirection) const = 0;

 public:
  Shape(Vector position, float scale, Color color,
        ReflectionType reflectionType,
        MaterialType materialType)  // Change here
      : position(position),
        scale(scale),
        materialType(materialType),
        Material(reflectionType, color, materialType) {}  // Pass materialType

  Shape(Vector position, Color color, ReflectionType reflectionType,
        MaterialType materialType)  // Change here
      : position(position),
        materialType(materialType),
        Material(reflectionType, color, materialType) {  // Pass materialType
    scale = 1;
  }

  virtual ~Shape() = default;

  Vector getPosition() const { return position; }

  float getScale() const { return scale; }

  virtual std::optional<Vector> getIntersectPoint(Ray ray) const = 0;

  virtual std::string toObjData(int& vertexIndex) const = 0;

  friend std::ostream& operator<<(std::ostream& _stream, Shape const& shape) {
    _stream << "(Position: " << shape.position << ", Scale: " << shape.scale
            << ")" << ", Material: " << static_cast<Material const&>(shape);
    return _stream;
  }
};
