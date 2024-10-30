#pragma once

#include <iostream>
#include <optional>

class Plan : public Shape {
 private:
  Vector normal;
  bool isVisible(Ray ray, Vector cameraPlanDirection) const override;
  bool isIntersect(float centerToTheoricIntersectPointLength) const;

 public:
  Plan(Vector position, Vector normal, ReflectionType reflectionType,
       Color color);
  Plan(Vector position, ReflectionType reflectionType, Color color);
  ~Plan() override = default;

  std::optional<Vector> getIntersectPoint(Ray ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Plan const& plan);
}