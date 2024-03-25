/*
** EPITECH PROJECT, 2024
** ArcadeShared
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "../../../include/common/utils/RGBAColor.hpp"
#include <cstddef>

#define CLAMP_COLOR(x) ((x) > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (x))

RGBAColor::RGBAColor(size_t r, size_t g, size_t b, size_t a) {
  this->_r = CLAMP_COLOR(r);
  this->_g = CLAMP_COLOR(g);
  this->_b = CLAMP_COLOR(b);
  this->_a = CLAMP_COLOR(a);
}

RGBAColor::RGBAColor(const RGBAColor &color) {
  this->_r = color.getR();
  this->_g = color.getG();
  this->_b = color.getB();
  this->_a = color.getA();
}

RGBAColor::RGBAColor() {
  this->_r = MIN_COLOR_VALUE;
  this->_g = MIN_COLOR_VALUE;
  this->_b = MIN_COLOR_VALUE;
  this->_a = MAX_COLOR_VALUE;
}

RGBAColor::~RGBAColor() {}

size_t RGBAColor::getR() const { return this->_r; }
size_t RGBAColor::getG() const { return this->_g; }
size_t RGBAColor::getB() const { return this->_b; }
size_t RGBAColor::getA() const { return this->_a; }

void RGBAColor::setR(size_t r) { this->_r = CLAMP_COLOR(r); }
void RGBAColor::setG(size_t g) { this->_g = CLAMP_COLOR(g); }
void RGBAColor::setB(size_t b) { this->_b = CLAMP_COLOR(b); }
void RGBAColor::setA(size_t a) { this->_a = CLAMP_COLOR(a); }

void RGBAColor::setRGBA(size_t r, size_t g, size_t b, size_t a) {
  this->setR(r);
  this->setG(g);
  this->setB(b);
  this->setA(a);
}

void RGBAColor::setRGB(size_t r, size_t g, size_t b) {
  this->setR(r);
  this->setG(g);
  this->setB(b);
}

// Operators

RGBAColor &RGBAColor::operator=(const RGBAColor &color) {
  this->_r = color.getR();
  this->_g = color.getG();
  this->_b = color.getB();
  this->_a = color.getA();
  return *this;
}

bool RGBAColor::operator==(const RGBAColor &color) const {
  return (this->_r == color.getR() && this->_g == color.getG() &&
          this->_b == color.getB() && this->_a == color.getA());
}

bool RGBAColor::operator!=(const RGBAColor &color) const {
  return !(*this == color);
}

RGBAColor RGBAColor::operator+(const RGBAColor &color) const {
  return RGBAColor(this->_r + color.getR(), this->_g + color.getG(),
                   this->_b + color.getB(), this->_a + color.getA());
}

RGBAColor RGBAColor::operator-(const RGBAColor &color) const {
  return RGBAColor(this->_r - color.getR(), this->_g - color.getG(),
                   this->_b - color.getB(), this->_a - color.getA());
}

RGBAColor RGBAColor::operator*(const RGBAColor &color) const {
  return RGBAColor(this->_r * color.getR(), this->_g * color.getG(),
                   this->_b * color.getB(), this->_a * color.getA());
}

RGBAColor RGBAColor::operator/(const RGBAColor &color) const {
  return RGBAColor(this->_r / color.getR(), this->_g / color.getG(),
                   this->_b / color.getB(), this->_a / color.getA());
}

RGBAColor RGBAColor::operator+(const size_t &value) const {
  return RGBAColor(this->_r + value, this->_g + value, this->_b + value,
                   this->_a + value);
}

RGBAColor RGBAColor::operator-(const size_t &value) const {
  return RGBAColor(this->_r - value, this->_g - value, this->_b - value,
                   this->_a - value);
}

RGBAColor RGBAColor::operator*(const float &value) const {
  return RGBAColor(this->_r * value, this->_g * value, this->_b * value,
                   this->_a * value);
}

RGBAColor RGBAColor::operator/(const float &value) const {
  return RGBAColor(this->_r / value, this->_g / value, this->_b / value,
                   this->_a / value);
}

RGBAColor &RGBAColor::operator+=(const RGBAColor &color) {
  *this = *this + color;
  return *this;
}

RGBAColor &RGBAColor::operator-=(const RGBAColor &color) {
  *this = *this - color;
  return *this;
}

RGBAColor &RGBAColor::operator*=(const RGBAColor &color) {
  *this = *this * color;
  return *this;
}

RGBAColor &RGBAColor::operator/=(const RGBAColor &color) {
  *this = *this / color;
  return *this;
}

RGBAColor &RGBAColor::operator+=(const size_t &value) {
  *this = *this + value;
  return *this;
}

RGBAColor &RGBAColor::operator-=(const size_t &value) {
  *this = *this - value;
  return *this;
}

RGBAColor &RGBAColor::operator*=(const float &value) {
  *this = *this * value;
  return *this;
}

RGBAColor &RGBAColor::operator/=(const float &value) {
  *this = *this / value;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const RGBAColor &color) {
  os << "(" << color.getR() << ", " << color.getG() << ", " << color.getB()
     << ", " << color.getA() << ")";
  return os;
}
