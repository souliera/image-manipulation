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
	ImagePGM empty;
	ImagePGM img(10, 10, 255);

	REQUIRE(empty.get_width() == 0);
	REQUIRE(empty.get_height() == 0);
	REQUIRE(empty.get_max_value() == 255);
	REQUIRE(img.get_width() == 10);
	REQUIRE(img.get_height() == 10);
	REQUIRE(img.get_max_value() == 255);

	int i[5];
	int j[5];
	int v[5];

	for(int k = 0; k < 5; k++) {
		i[k] = std::rand() % 10;
		j[k] = std::rand() % 10;
		v[k] = std::rand() % 255;
		img.set_pixel(i[k], j[k], v[k]);
	}

	for(std::uint16_t y = 0; y < 10; y++) {
		for(std::uint16_t x = 0; x < 10; x++) {
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

	CHECK_THROWS_AS(img.set_pixel(10, 0, 0), std::out_of_range);
	CHECK_THROWS_AS(img.set_pixel(0, 10, 0), std::out_of_range);
	CHECK_THROWS_AS(empty.set_pixel(1, 1, 0), std::out_of_range);
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

TEST_CASE("Image PGM: laod_image", "[ImagePGM][constructors][io]") {
	SECTION("Binary image") {
		ImagePGM img("rsc/lena.pgm");

		CHECK(img.get_magic_number().compare("P5") == 0);
		CHECK(img.get_width() == 512);
		CHECK(img.get_height() == 512);
		CHECK(img.get_max_value() == 255);

		CHECK(img.get_pixel(211, 25) == 124);
		CHECK(img.get_pixel(316, 434) == 176);
		CHECK(img.get_pixel(283, 273) == 153);
		CHECK(img.get_pixel(400, 184) == 48);
		CHECK(img.get_pixel(127, 202) == 216);
	}

	SECTION("ASCII image") {
		ImagePGM img("rsc/lena.ascii.pgm");

		CHECK(img.get_magic_number().compare("P2") == 0);
		CHECK(img.get_width() == 512);
		CHECK(img.get_height() == 512);
		CHECK(img.get_max_value() == 245);

		CHECK(img.get_pixel(0, 0) == 162);
		CHECK(img.get_pixel(185, 426) == 31);
		CHECK(img.get_pixel(384, 157) == 205);
		CHECK(img.get_pixel(73, 393) == 52);
		CHECK(img.get_pixel(77, 474) == 55);
		CHECK(img.get_pixel(412, 429) == 133);
	}
}

TEST_CASE("Image PGM: resize", "[ImagePGM][size]") {
	ImagePGM img(5, 5, 255);

	for(std::uint16_t y = 0; y < 5; y++) {
		for(std::uint16_t x = 0; x < 5; x++) {
			img.set_pixel(x, y, y * 5 + x);
		}
	}

	REQUIRE(img.get_width() == 5);
	REQUIRE(img.get_height() == 5);
	for(std::uint16_t y = 0; y < 5; y++) {
		for(std::uint16_t x = 0; x < 5; x++) {
			REQUIRE(img.get_pixel(x, y) == y * 5 + x);
		}
	}
	REQUIRE(img.get_max_value() == 255);
	
	SECTION("Increase size") {
		img.resize(7, 7);

		CHECK(img.get_width() == 7);
		CHECK(img.get_height() == 7);

		for(std::uint16_t y = 0; y < 6; y++) {
			for(std::uint16_t x = 0; x < 6; x++) {
				if(y >= 5 || x >= 5) {
					CHECK(img.get_pixel(x, y) == 0);
				} else {
					CHECK(img.get_pixel(x, y) ==  y * 5 + x);
				}
			}
		}
	}

	SECTION("Decrease size") {
		img.resize(3, 3);

		CHECK(img.get_width() == 3);
		CHECK(img.get_height() == 3);

		for(std::uint16_t y = 0; y < 3; y++) {
			for(std::uint16_t x = 0; x < 3; x++) {
				CHECK(img.get_pixel(x, y) == y * 5 + x);
			}
		}
	}

	CHECK_THROWS_AS(img.resize(0, 5), std::invalid_argument);
	CHECK_THROWS_AS(img.resize(5, 0), std::invalid_argument);
}
