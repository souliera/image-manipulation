#include "image_pgm.hpp"

ImagePGM::ImagePGM() : ImagePGM(0, 0, 255) {}

ImagePGM::ImagePGM(const std::uint16_t &width, const std::uint16_t &height, const std::uint16_t &maxValue) : _width(width), _height(height), _pixels(width * height, 0), _magicNumber("P5"), _maxValue(maxValue) {}


std::uint16_t ImagePGM::get_width() const {
	return this->_width;
}

std::uint16_t ImagePGM::get_height() const {
	return this->_height;
}

std::uint16_t ImagePGM::get_pixel(const std::uint16_t &x, const std::uint16_t &y) const {
	return this->_pixels[y * _width + x];
}

std::string ImagePGM::get_magic_number() const {
	return this->_magicNumber;
}

std::uint16_t ImagePGM::get_max_value() const {
	return this->_maxValue;
}
