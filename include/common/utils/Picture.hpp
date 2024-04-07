/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/utils/IPicture.hpp"
#include <ostream>

class Picture: public IPicture {
protected:
    std::string _path;
    std::size_t _width;
    std::size_t _height;
public:
    /**
     * @brief Construct a new Picture object
     * @param path the path to the picture
     * @param width the width of the picture
     * @param height the height of the picture
     */
    Picture(const std::string &path, std::size_t width, std::size_t height);
    /**
     * @brief Construct a new Picture object from an IPicture object
     * @param picture the IPicture object to copy
     */
    Picture(const IPicture &picture);
    /**
     * @brief Construct a new Picture object
     * The path is empty
     * The width and height are 0
     */
    Picture();
    /**
     * @brief Destroy the Picture object
     */
    ~Picture() override;
    /**
     * @brief Get the path of the picture
     * @return The path of the picture
     */
    [[nodiscard]] const std::string &getPath() const override;
    /**
     * @brief Set the path of the picture
     * @param path The new path of the picture
     */
    void setPath(const std::string &path) override;
    /**
     * @brief Get the width of the picture
     * @return The width of the picture
     */
    [[nodiscard]] std::size_t getWidth() const override;
    /**
     * @brief Get the height of the picture
     * @return The height of the picture
     */
    [[nodiscard]] std::size_t getHeight() const override;

    // Operators
    /**
     * @brief Compare two Picture objects
     * @param picture The Picture object to compare with
     * @return true if the path of the two pictures are the same, false otherwise
     */
    bool operator==(const Picture &picture) const;
    /**
     * @brief Compare two Picture objects
     * @param picture The Picture object to compare with
     * @return false if the path of the two pictures are the same, true otherwise
     */
    bool operator!=(const Picture &picture) const;
    /**
     * @brief Assign a Picture object to another
     * @param picture The Picture object to assign
     * @return The Picture object assigned
     */
    Picture &operator=(const Picture &picture);
    /**
     * @brief Output the path of the picture
     * @param os The output stream
     * @param picture The Picture object to output
     * @return The output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Picture &picture);
};
