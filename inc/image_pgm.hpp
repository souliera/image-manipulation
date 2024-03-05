#ifndef DEF_IMAGE_PGM_HPP
#define DEF_IMAGE_PGM_HPP

/**
 * @brief File for the image class in PGM format.
 * @file image_pgm.hpp
 * @author Arnaud Soulier
 * @date 5 mar. 2024
 * @version 0.2.0
 */

#include <cstdint> /* (u)intX_t */
#include <vector> /* vector class */
#include <string> /* string class, to_string */
#include <stdexcept> /* out_of_range, invalid_argument */

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

		std::uint16_t get_width() const;
		std::uint16_t get_height() const;
		std::uint16_t get_pixel(const std::uint16_t &x, const std::uint16_t &y) const;
		std::string get_magic_number() const;
		std::uint16_t get_max_value() const;

		void set_pixel(const std::uint16_t &x, const std::uint16_t &y, const std::uint16_t &value);
		void set_magic_number(const std::string &magicNumber);
		void set_max_value(const std::uint16_t &maxValue);
};

#endif
