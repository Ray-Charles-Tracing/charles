#include "../../include/raymath/Light.hpp"

Light::Light() : color(Color()), position(Vector()) { shiningCoef = 32.0f; }

Light::Light(Color const& color, Vector const& position, float shiningCoef)
    : color(color), position(position), shiningCoef(shiningCoef) {}

Light::Light(Color const& color, Vector const& position)
    : color(color), position(position) {
  shiningCoef = 32.0f;
}

Light::~Light() {}

Color Light::getColor() const { return color; }

Vector Light::getPosition() const { return position; }

float Light::getShiningCoef() const { return shiningCoef; }

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
