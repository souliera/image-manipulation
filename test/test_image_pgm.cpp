#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cstdlib>
#include <ctime>

#include "image_pgm.hpp"

TEST_CASE("Image PGM: empty constructor", "[ImagePGM][constructors]") {
	ImagePGM empty;

	std::uint16_t w = empty.get_width();
	std::uint16_t h = empty.get_height();

	CHECK(w == 0);
	CHECK(h == 0);

	for(std::uint16_t y = 0; y < h; y++) {
		for(std::uint16_t x = 0; x < w; x++) {
			CHECK(empty.get_pixel(x, y) == 0);
		}
	}

	CHECK(empty.get_magic_number().compare("P5") == 0);
	CHECK(empty.get_max_value() == 255);
}

TEST_CASE("Image PGM: size constructor", "[ImagePGM][constructors]") {
	std::srand(std::time(nullptr));

	std::uint16_t width = std::rand() % 512;
	std::uint16_t height = std::rand() % 512;
	std::uint16_t max = std::rand() % 255;

	ImagePGM img(width, height, max);

	std::uint16_t w = img.get_width();
	std::uint16_t h = img.get_height();

	CHECK(w == width);
	CHECK(h == height);

	for(std::uint16_t y = 0; y < h; y++) {
		for(std::uint16_t x = 0; x < w; x++) {
			CHECK(img.get_pixel(x, y) == 0);
		}
	}

	CHECK(img.get_magic_number().compare("P5") == 0);
	CHECK(img.get_max_value() == max);
}
