#ifndef DEF_IMAGE_PGM_HPP
#define DEF_IMAGE_PGM_HPP

/**
 * @brief File for the image class in PGM format.
 * @file image_pgm.hpp
 * @author Arnaud Soulier
 * @date 28 feb. 2024
 * @version 0.1.0
 */

#include <cstdint> /* (u)intX_t */
#include <vector> /* vector class */
#include <string> /* string class */

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
};

#endif
