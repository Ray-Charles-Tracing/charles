#include "../../include/raymath/Color.hpp"

#include <cmath>
#include <iostream>

Color::Color() : r(0), b(0), g(0) {}

Color::Color(float iR, float iG, float iB) : r(iR), g(iG), b(iB) {}

Color::~Color() {}

float Color::R() { return r; }

float Color::G() { return g; }

float Color::B() { return b; }

/**
 * Implementation of the + operator :
 * Adding two colors is done by just adding the different components together :
 * (r1, g1, b1) + (r2, g2, b2) = (r1 + r2, g1 + g2, b1 + b2)
 */
Color Color::operator+(Color const &col) {
  Color c;
  c.r = fmax(fmin(r + col.r, 1), 0);
  c.g = fmax(fmin(g + col.g, 1), 0);
  c.b = fmax(fmin(b + col.b, 1), 0);
  return c;
}

/**
 * Implementation of the * operator :
 * Adjusting the intensity of a color by multiplying each component by the
 * intensity factor.
 *
 * The intensity factor is a value between 0 and 1, representing the angle of
 * the object relative to the light source. A value of 0 means no illumination,
 * while a value of 1 means full illumination.
 */
Color Color::operator*(float intensity) const {
  Color c;
  c.r = fmax(fmin(r * intensity, 1), 0);
  c.g = fmax(fmin(g * intensity, 1), 0);
  c.b = fmax(fmin(b * intensity, 1), 0);
  return c;
}

/**
 * Overriding the assignment operator
 */
Color &Color::operator=(Color const &col) {
  r = col.r;
  g = col.g;
  b = col.b;
  return *this;
}

/**
 * Here we implement the << operator :
 * We take each component and append it to he stream, giving it a nice form on
 * the console
 */
std::ostream &operator<<(std::ostream &_stream, Color const &col) {
  return _stream << "(" << col.r << "," << col.g << "," << col.b << ")";
}
