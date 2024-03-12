#ifndef DEF_IMAGE_PGM_HPP
#define DEF_IMAGE_PGM_HPP

/**
 * @brief File for the image class in PGM format.
 * @file image_pgm.hpp
 * @author Arnaud Soulier
 * @date 12 mar. 2024
 * @version 0.5.1
 */

#include <cstdint> /* (u)intX_t */
#include <vector> /* vector class */
#include <string> /* string class, to_string */
#include <stdexcept> /* out_of_range, invalid_argument */
#include <fstream> /* ifstream class */
#include <sstream> /* stringstream class */
#include <cstring> /* memset */
#include <cmath> /* ceil */

/**
 * @class ImagePGM
 * @brief Class for the PGM image format.
 */
class ImagePGM {
	private:
		std::uint16_t _width; /** Image width */
		std::uint16_t _height; /** Image height */
		std::vector<std::uint16_t> _pixels; /** Image pixel array */
		std::string _magicNumber; /** Magic number of the image */
		std::uint16_t _maxValue; /** Maximum value of an image pixel */

	public:
		/*
		 * ####################
		 * ### CONSTRUCTORS ###
		 * ####################
		 */

		/**
		 * Constructs an empty image instance with no pixels and default maximum pixel value of 255.
		 *
		 * @brief Empty constructor
		 */
		ImagePGM();
		/**
		 * Constructs an image instance with the given dimensions and maximum pixel value.
		 *
		 * @brief Size constructor
		 * @param[in] width the width of the image instance
		 * @param[in] height the height of the image instance
		 * @param[in] maxValue the maximum pixel value of the image instance
		 */
		ImagePGM(const std::uint16_t &width, const std::uint16_t &height, const std::uint16_t &maxValue);
		/**
		 * Constructs an image instance with the digital image at the given path.
		 *
		 * @brief File constructor
		 * @param[in] filepath the path of the digital image file
		 */
		ImagePGM(const std::string &filepath);

		/*
		 * #################
		 * ### ACCESSORS ###
		 * #################
		 */

		/**
		 * Returns the width of the image instance.
		 *
		 * @brief Width getter
		 * @return the width of the image
		 */
		std::uint16_t get_width() const;
		/**
		 * Returns the height of the image instance.
		 *
		 * @brief Height getter
		 * @return the height of the image
		 */
		std::uint16_t get_height() const;
		/**
		 * Returns the pixel value of the image instance at the given coordinates.
		 *
		 * @brief Pixel getter
		 * @param[in] x the coordinate of the image along the width
		 * @param[in] y the coordinate of the image along the height
		 * @return the value of the image pixel
		 */
		std::uint16_t get_pixel(const std::uint16_t &x, const std::uint16_t &y) const;
		/**
		 *
		 * Returns the magic number of the image instance.
		 *
		 * @brief Magic number getter
		 * @return the magic number of the image
		 */
		std::string get_magic_number() const;
		/**
		 * Returns the maximum pixel value of the image instance.
		 *
		 * @brief Maximum pixel value getter
		 */
		std::uint16_t get_max_value() const;

		/**
		 * Defines the value of a pixel of the image instance at the given coordinates.
		 *
		 * @brief Pixel setter
		 * @param[in] x the coordinate of the image along the width
		 * @param[in] y the coordinate of the image along the height
		 * @param[in] value the new value of the pixel
		 */
		void set_pixel(const std::uint16_t &x, const std::uint16_t &y, const std::uint16_t &value);
		/**
		 * Defines the magic number of the image instance.
		 *
		 * @brief Magic number setter
		 * @param[in] magicNumber the new magix number of the image
		 */
		void set_magic_number(const std::string &magicNumber);
		/**
		 * Defines the maximum pixel value of the image instance.
		 *
		 * @brief Maximum pixel value setter
		 * @param[in] maxValue the new maximum pixel value of the image
		 */
		void set_max_value(const std::uint16_t &maxValue);

		/*
		 * ###############
		 * ### METHODS ###
		 * ###############
		 */

	private:
		/**
		 * Reads a digital image file to set the image instance.
		 *
		 * @brief Image file loader
		 * @param[in] filepath the path of the digital image file
		 */
		void load_image(const std::string &filepath);
		/**
		 * Reads the binary data of the digital image.
		 *
		 * @brief Binary loader
		 * @param[in] input the input stream of the digital image file
		 */
		void load_binary(std::ifstream &input);
		/**
		 * Reads the ASCII data of the digital image.
		 *
		 * @brief ASCII loader
		 * @param[in] input the input stream of the digital image file
		 */
		void load_ascii(std::ifstream &input);

	public:
		/**
		 * Writes a digital image file by the image instance.
		 *
		 * @brief Image file saver
		 * @param[in] filepath the path of the digital image file
		 */
		void save_image(const std::string&filepath) const;
		/**
		 * Writes the binary data of the image instance.
		 *
		 * @brief Binary saver
		 * @param[in] output the output stream of the digital image file
		 */
		void save_binary(std::ofstream &output) const;
		/**
		 * Writes the ASCII	 data of the image instance.
		 *
		 * @brief ASCII saver
		 * @param[in] output the output stream of the digital image file
		 */
		void save_ascii(std::ofstream &output) const;

		/**
		 * Resize the image instance.
		 *
		 * @brief Image resizer
		 * @param[in] width the new width of the image
		 * @param[in] height the new height of the image
		 */
		void resize(const std::uint16_t &width, const std::uint16_t &height);
};

#endif
