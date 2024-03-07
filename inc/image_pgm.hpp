#ifndef DEF_IMAGE_PGM_HPP
#define DEF_IMAGE_PGM_HPP

/**
 * @brief File for the image class in PGM format.
 * @file image_pgm.hpp
 * @author Arnaud Soulier
 * @date 7 mar. 2024
 * @version 0.3.0
 */

#include <cstdint> /* (u)intX_t */
#include <vector> /* vector class */
#include <string> /* string class, to_string */
#include <stdexcept> /* out_of_range, invalid_argument */
#include <fstream> /* ifstream class */
#include <sstream> /* stringstream class */

/**
 * @class ImagePGM
 * @brief Class for the PGM image format.
 */
class ImagePGM {
	private:
		std::uint16_t _width;
		std::uint16_t _height;
		std::vector<std::uint16_t> _pixels;
		std::string _magicNumber;
		std::uint16_t _maxValue;

	public:
		ImagePGM();
		ImagePGM(const std::uint16_t &width, const std::uint16_t &height, const std::uint16_t &maxValue);
		ImagePGM(const std::string &filepath);

		std::uint16_t get_width() const;
		std::uint16_t get_height() const;
		std::uint16_t get_pixel(const std::uint16_t &x, const std::uint16_t &y) const;
		std::string get_magic_number() const;
		std::uint16_t get_max_value() const;

		void set_pixel(const std::uint16_t &x, const std::uint16_t &y, const std::uint16_t &value);
		void set_magic_number(const std::string &magicNumber);
		void set_max_value(const std::uint16_t &maxValue);

	private:
		void load_image(const std::string &filepaht);
		void load_binary(std::ifstream &input);
		void load_ascii(std::ifstream &input);
};

#endif
