#pragma once

#include <iostream>

#include "Color.hpp"
#include "Vector.hpp"

class Light {
 private:
  Color color;
  Vector position;

 public:
  Light();
  Light(Color const& color, Vector const& position);
  ~Light();

  Color getColor() const;
  Vector getPosition() const;

  void setColor(Color const& color);
  void setPosition(Vector const& position);

  friend std::ostream& operator<<(std::ostream& _stream, Light const& light);
};
