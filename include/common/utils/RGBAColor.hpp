/*
** EPITECH PROJECT, 2024
** ArcadeShared
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/utils/IColor.hpp"
#include <cstddef>
#include <ostream>

#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

class RGBAColor : public IColor {
protected:
  size_t _r;
  size_t _g;
  size_t _b;
  size_t _a;

public:
  RGBAColor(size_t r, size_t g, size_t b, size_t a = 255);
  RGBAColor(const IColor &color);
  RGBAColor();
  ~RGBAColor() override;
  size_t getR() const override;
  size_t getG() const override;
  size_t getB() const override;
  size_t getA() const override;
  void setR(size_t r) override;
  void setG(size_t g) override;
  void setB(size_t b) override;
  void setA(size_t a) override;
  void setRGBA(size_t r, size_t g, size_t b, size_t a) override;
  void setRGB(size_t r, size_t g, size_t b) override;

  // Static colors
  static const RGBAColor BLACK;
  static const RGBAColor WHITE;
  static const RGBAColor RED;
  static const RGBAColor GREEN;
  static const RGBAColor BLUE;
  static const RGBAColor YELLOW;
  static const RGBAColor MAGENTA;
  static const RGBAColor CYAN;
  static const RGBAColor TRANSPARENT;

  // Operators overloading
  bool operator==(const RGBAColor &color) const;
  bool operator!=(const RGBAColor &color) const;
  RGBAColor &operator=(const RGBAColor &color);
  RGBAColor operator+(const RGBAColor &color) const;
  RGBAColor operator-(const RGBAColor &color) const;
  RGBAColor operator*(const RGBAColor &color) const;
  RGBAColor operator/(const RGBAColor &color) const;
  RGBAColor operator+(const size_t &value) const;
  RGBAColor operator-(const size_t &value) const;
  RGBAColor operator*(const float &value) const;
  RGBAColor operator/(const float &value) const;
  RGBAColor &operator+=(const RGBAColor &color);
  RGBAColor &operator-=(const RGBAColor &color);
  RGBAColor &operator*=(const RGBAColor &color);
  RGBAColor &operator/=(const RGBAColor &color);
  RGBAColor &operator+=(const size_t &value);
  RGBAColor &operator-=(const size_t &value);
  RGBAColor &operator*=(const float &value);
  RGBAColor &operator/=(const float &value);
  friend std::ostream &operator<<(std::ostream &os, const RGBAColor &color);
};
