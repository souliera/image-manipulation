#include "image_pgm.hpp"

ImagePGM::ImagePGM() : ImagePGM(0, 0, 255) {}

ImagePGM::ImagePGM(const std::uint16_t &width, const std::uint16_t &height, const std::uint16_t &maxValue) : _width(width), _height(height), _pixels(width * height, 0), _magicNumber("P5"), _maxValue(maxValue) {}
