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

TEST_CASE("Image PGM: set_pixel", "[ImagePGM][setters]") {
	ImagePGM img(5, 5, 255);

	REQUIRE(img.get_width() == 5);
	REQUIRE(img.get_height() == 5);
	REQUIRE(img.get_max_value() == 255);

	int i[5];
	int j[5];
	int v[5];

	for(int k = 0; k < 5; k++) {
		i[k] = std::rand() % 5;
		j[k] = std::rand() % 5;
		v[k] = std::rand() % 255;
		img.set_pixel(i[k], j[k], v[k]);
	}

	for(std::uint16_t y = 0; y < 5; y++) {
		for(std::uint16_t x = 0; x < 5; x++) {
			for(int k = 0; k < 5; k++) {
				if(y == j[k] && x == i[k]) {
					CHECK(img.get_pixel(x, y) == v[k]);
					break;
				} else if(k < 4) {
					continue;
				}
			
				CHECK(img.get_pixel(x, y) == 0);
			}
		}
	}

	CHECK_THROWS_AS(img.set_pixel(5, 0, 0), std::out_of_range);
	CHECK_THROWS_AS(img.set_pixel(0, 5, 0), std::out_of_range);
}

TEST_CASE("Image PGM: set_magic_number", "[ImagePGM][setters]") {
	ImagePGM img(5, 5, 255);

	REQUIRE(img.get_width() == 5);
	REQUIRE(img.get_height() == 5);
	REQUIRE(img.get_max_value() == 255);

	img.set_magic_number("P2");
	CHECK(img.get_magic_number().compare("P2") == 0);
	img.set_magic_number("P5");
	CHECK(img.get_magic_number().compare("P5") == 0);

	CHECK_THROWS_AS(img.set_magic_number("P1"), std::invalid_argument);
	CHECK_NOTHROW(img.set_magic_number("P2"));
	CHECK_THROWS_AS(img.set_magic_number("P3"), std::invalid_argument);
	CHECK_THROWS_AS(img.set_magic_number("P4"), std::invalid_argument);
	CHECK_NOTHROW(img.set_magic_number("P5"));
	CHECK_THROWS_AS(img.set_magic_number("P6"), std::invalid_argument);
}

TEST_CASE("Image PGM: set_max_value", "[ImagePGM][setters]") {
	ImagePGM img(5, 5, 255);

	REQUIRE(img.get_width() == 5);
	REQUIRE(img.get_height() == 5);
	REQUIRE(img.get_max_value() == 255);

	std::uint16_t max = std::rand() % 255;
	img.set_max_value(max);
	CHECK(img.get_max_value() == max);
}
