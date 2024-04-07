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
    /**
     * @brief Construct a new RGBAColor object
     * @param r The red component of the color
     * @param g The green component of the color
     * @param b The blue component of the color
     * @param a The alpha component of the color (default is 255)
     */
    RGBAColor(size_t r, size_t g, size_t b, size_t a = 255);
    /**
     * @brief Construct a new RGBAColor object from an IColor object
     * @param color The IColor object to copy
     */
    explicit RGBAColor(const IColor &color);
    /**
     * @brief Construct a new RGBAColor object (transparent black, 0, 0, 0, 0)
     */
    RGBAColor();
    /**
     * @brief Destroy the RGBAColor object
     */
    ~RGBAColor() override;
    /**
     * @brief Get the red component of the color
     * @return The red component of the color
     */
    [[nodiscard]] std::size_t getR() const override;
    /**
     * @brief Get the green component of the color
     * @return The green component of the color
     */
    [[nodiscard]] std::size_t getG() const override;
    /**
     * @brief Get the blue component of the color
     * @return The blue component of the color
     */
    [[nodiscard]] std::size_t getB() const override;
    /**
     * @brief Get the alpha component of the color
     * @return The alpha component of the color
     */
    [[nodiscard]] std::size_t getA() const override;
    /**
     * @brief Set the red component of the color
     * @param r The red component of the color (Will be clamped between 0 and 255)
     */
    void setR(std::size_t r) override;
    /**
     * @brief Set the green component of the color
     * @param g The green component of the color (Will be clamped between 0 and 255)
     */
    void setG(std::size_t g) override;
    /**
     * @brief Set the blue component of the color
     * @param b The blue component of the color (Will be clamped between 0 and 255)
     */
    void setB(std::size_t b) override;
    /**
     * @brief Set the alpha component of the color
     * @param a The alpha component of the color (Will be clamped between 0 and 255)
     */
    void setA(std::size_t a) override;
    /**
     * @brief Set the RGBA components of the color
     * @param r the red component of the color
     * @param g the green component of the color
     * @param b the blue component of the color
     * @param a the alpha component of the color
     * @note All components will be clamped between 0 and 255
     */
    void setRGBA(size_t r, size_t g, size_t b, size_t a) override;
    /**
     * @brief Set the RGB components of the color
     * @param r the red component of the color
     * @param g the green component of the color
     * @param b the blue component of the color
     * @note All components will be clamped between 0 and 255
     */
    void setRGB(size_t r, size_t g, size_t b) override;

    // Static colors
    /**
     * @brief A constant representing the black color (0, 0, 0, 255)
     */
    static const RGBAColor BLACK;
    /**
     * @brief A constant representing the white color (255, 255, 255, 255)
     */
    static const RGBAColor WHITE;
    /**
     * @brief A constant representing the red color (255, 0, 0, 255)
     */
    static const RGBAColor RED;
    /**
     * @brief A constant representing the green color (0, 255, 0, 255)
     */
    static const RGBAColor GREEN;
    /**
     * @brief A constant representing the blue color (0, 0, 255, 255)
     */
    static const RGBAColor BLUE;
    /**
     * @brief A constant representing the yellow color (255, 255, 0, 255)
     */
    static const RGBAColor YELLOW;
    /**
     * @brief A constant representing the magenta color (255, 0, 255, 255)
     */
    static const RGBAColor MAGENTA;
    /**
     * @brief A constant representing the cyan color (0, 255, 255, 255)
     */
    static const RGBAColor CYAN;
    /**
     * @brief A constant representing the transparent color (0, 0, 0, 0)
     */
    static const RGBAColor TRANSPARENT;

    // Operators overloading
    /**
     * @brief Check if two colors are equal
     * @param color The color to compare with
     * @return true if the colors are equal, false otherwise
     */
    bool operator==(const RGBAColor &color) const;
    /**
     * @brief Check if two colors are different
     * @param color The color to compare with
     * @return true if the colors are different, false otherwise
     */
    bool operator!=(const RGBAColor &color) const;
    /**
     * @brief Assign a color to another
     * @param color The color to assign
     * @return The assigned color
     */
    RGBAColor &operator=(const RGBAColor &color);
    /**
     * @brief Add two colors
     * @param color The color to add
     * @return The result of the addition
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator+(const RGBAColor &color) const;
    /**
     * @brief Subtract two colors
     * @param color The color to subtract
     * @return The result of the subtraction
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator-(const RGBAColor &color) const;
    /**
     * @brief Multiply two colors
     * @param color The color to multiply
     * @return The result of the multiplication
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator*(const RGBAColor &color) const;
    /**
     * @brief Divide two colors
     * @param color The color to divide
     * @return The result of the division
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator/(const RGBAColor &color) const;
    /**
     * @brief Add a value to all components of the color
     * @param value The value to add
     * @return The result of the addition
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator+(const std::size_t &value) const;
    /**
     * @brief Subtract a value to all components of the color
     * @param value The value to subtract
     * @return The result of the subtraction
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator-(const std::size_t &value) const;
    /**
     * @brief Multiply all components of the color by a value
     * @param value The value to multiply
     * @return The result of the multiplication
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator*(const float &value) const;
    /**
     * @brief Divide all components of the color by a value
     * @param value The value to divide
     * @return The result of the division
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor operator/(const float &value) const;
    /**
     * @brief Add a color to another
     * @param color The color to add
     * @return The result of the addition
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator+=(const RGBAColor &color);
    /**
     * @brief Subtract a color to another
     * @param color The color to subtract
     * @return The result of the subtraction
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator-=(const RGBAColor &color);
    /**
     * @brief Multiply a color to another
     * @param color The color to multiply
     * @return The result of the multiplication
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator*=(const RGBAColor &color);
    /**
     * @brief Divide a color to another
     * @param color The color to divide
     * @return The result of the division
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator/=(const RGBAColor &color);
    /**
     * @brief Add a value to all components of the color
     * @param value The value to add
     * @return The result of the addition
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator+=(const std::size_t &value);
    /**
     * @brief Subtract a value to all components of the color
     * @param value The value to subtract
     * @return The result of the subtraction
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator-=(const std::size_t &value);
    /**
     * @brief Multiply all components of the color by a value
     * @param value The value to multiply
     * @return The result of the multiplication
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator*=(const float &value);
    /**
     * @brief Divide all components of the color by a value
     * @param value The value to divide
     * @return The result of the division
     * @note All result's components are clamped between 0 and 255
     */
    RGBAColor &operator/=(const float &value);
    /**
     * @brief Output the color to an output stream
     * @param os The output stream
     * @param color The color to output
     * @return The output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const RGBAColor &color);
};
