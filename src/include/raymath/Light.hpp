#pragma once

#include <iostream>

#include "Color.hpp"
#include "Vector.hpp"

class Light {
 private:
  Color color;
  Vector position;
  float shiningCoef;

 public:
  Light();
  Light(Color const& color, Vector const& position, float shiningCoef);
  Light(Color const& color, Vector const& position);
  ~Light();

  Color getColor() const;
  Vector getPosition() const;
  float getShiningCoef() const;

  void setColor(Color const& color);
  void setPosition(Vector const& position);

  friend std::ostream& operator<<(std::ostream& _stream, Light const& light);
};
