#include "image_pgm.hpp"

#include <iostream>

ImagePGM::ImagePGM() : ImagePGM(0, 0, 255) {}

ImagePGM::ImagePGM(const std::uint16_t &width, const std::uint16_t &height, const std::uint16_t &maxValue) : _width(width), _height(height), _pixels(width * height, 0), _magicNumber("P5"), _maxValue(maxValue) {}

ImagePGM::ImagePGM(const std::string &filepath) : _width(0), _height(0), _magicNumber(""), _maxValue(0) {
	this->load_image(filepath);
}

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
	//TODO check _width & _height == 0

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

void ImagePGM::load_image(const std::string &filepath) {
	std::ifstream input(filepath, std::ios::in | std::ios::binary);

	const int BUFF_SIZE = 512;
	unsigned char buffer[BUFF_SIZE];
	std::stringstream sstr;
	do {
		input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
		sstr.str(reinterpret_cast<char*>(buffer));
		sstr.clear();
	} while(sstr.str()[0] == '#');

	// read magic number
	while(_magicNumber.compare("") == 0) {
		if(sstr >> _magicNumber) {
		} else {
			do {
				input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
				sstr.str(reinterpret_cast<char*>(buffer));
				sstr.clear();
			} while(sstr.str()[0] == '#');
		}
	}
	
	// read width and height
	while(_width == 0) {
		if(sstr >> _width) {
		} else {
			do {
				input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
				sstr.str(reinterpret_cast<char*>(buffer));
				sstr.clear();
			} while(sstr.str()[0] == '#');
		}
	}

	while(_height == 0) {
		if(sstr >> _height) {
		} else {
			do {
				input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
				sstr.str(reinterpret_cast<char*>(buffer));
				sstr.clear();
			} while(sstr.str()[0] == '#');
		}
	}
	
	// read max value
	while(_maxValue == 0) {
		if(sstr >> _maxValue) {
		} else {
			do {
				input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
				sstr.str(reinterpret_cast<char*>(buffer));
				sstr.clear();
			} while(sstr.str()[0] == '#');
		}
	}

	_pixels.resize(_width * _height, 0);
	
	// read pixel values
	if(_magicNumber.compare("P5") == 0) {
		this->load_binary(input);
	} else {
		this->load_ascii(input);
	}
}

void ImagePGM::load_binary(std::ifstream &input) {
	const int BUFF_SIZE = 512;
	unsigned char buffer[BUFF_SIZE];
	std::uint16_t offset = 0;

	input.read(reinterpret_cast<char*>(buffer), BUFF_SIZE);
	for(std::uint16_t y = 0; y < _height; y++) {
		for(std::uint16_t x = 0; x < _width; x++) {
			if(_maxValue < 256) {
				_pixels[y * _width + x] = buffer[offset];
			} else {
				_pixels[y* _width + x] = (buffer[offset] << 8) & buffer[offset+1];
				offset++;
			}

			offset++;
			if(offset == BUFF_SIZE) {
				input.read(reinterpret_cast<char*>(buffer), BUFF_SIZE);
				offset = 0;
			}
		}
	}
}

void ImagePGM::load_ascii(std::ifstream &input) {
	const int BUFF_SIZE = 512;
	unsigned char buffer[BUFF_SIZE];
	std::stringstream sstr;

	input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
	sstr.str(reinterpret_cast<char*>(buffer));
	sstr.clear();
	
	for(std::uint16_t y = 0; y < _height; y++) {
		for(std::uint16_t x = 0; x < _width; x++) {
			sstr >> _pixels[y * _width + x];
			if(sstr.fail()) {
				x--;
			}
			if(sstr.eof()) {
				input.getline(reinterpret_cast<char*>(buffer), BUFF_SIZE);
				sstr.str(reinterpret_cast<char*>(buffer));
				sstr.clear();
			}
		}
	}
}
