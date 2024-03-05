#include "image_pgm.hpp"

ImagePGM::ImagePGM() : ImagePGM(0, 0, 255) {}

ImagePGM::ImagePGM(const std::uint16_t &width, const std::uint16_t &height, const std::uint16_t &maxValue) : _width(width), _height(height), _pixels(width * height, 0), _magicNumber("P5"), _maxValue(maxValue) {}


std::uint16_t ImagePGM::get_width() const {
	return _width;
}

std::uint16_t ImagePGM::get_height() const {
	return _height;
}

std::uint16_t ImagePGM::get_pixel(const std::uint16_t &x, const std::uint16_t &y) const {
	return _pixels[y * _width + x];
}

std::string ImagePGM::get_magic_number() const {
	return _magicNumber;
}

std::uint16_t ImagePGM::get_max_value() const {
	return _maxValue;
}

void ImagePGM::set_pixel(const std::uint16_t &x, const std::uint16_t &y, const std::uint16_t &value) {
	if(x >= _width) {
		throw std::out_of_range("method set_pixel(): x (" + std::to_string(x) + ") must be less of equal than the image width (" + std::to_string(_width) + ")");
	}
	if(y >= _height) {
		throw std::out_of_range("method set_pixel(): y (" + std::to_string(y) + ") must be less of equal than the image height (" + std::to_string(_height) + ")");
	}
	if(value >= _maxValue) {
		throw std::out_of_range("method set_pixel(): value (" + std::to_string(value) + ") must be less of equal than the image max value (" + std::to_string(_maxValue) + ")");
	}

	_pixels[y * _width + x] = value;
}

void ImagePGM::set_magic_number(const std::string &magicNumber) {
	if(magicNumber.compare("P2") != 0 && magicNumber.compare("P5") != 0) {
		throw std::invalid_argument("magic number must be P2 of P5 (get " + magicNumber + ")");
	}

	_magicNumber = magicNumber;
}

void ImagePGM::set_max_value(const std::uint16_t &maxValue) {
	_maxValue = maxValue;
}
