#include "../../include/raymath/Light.hpp"

Light::Light() : color(Color()), position(Vector()) {}

Light::Light(Color const& color, Vector const& position)
    : color(color), position(position) {}

Light::~Light() {}

Color Light::getColor() const { return color; }

Vector Light::getPosition() const { return position; }

void Light::setColor(Color const& color) { this->color = color; }

void Light::setPosition(Vector const& position) { this->position = position; }

/**
 * Here we implement the << operator :
 * We take each component and append it to he stream, giving it a nice form on
 * the console
 */
std::ostream& operator<<(std::ostream& _stream, Light const& light) {
  return _stream << "Light(Color: " << light.color
                 << ", Position: " << light.position << ")";
}
