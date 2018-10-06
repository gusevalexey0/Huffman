#include "gtest/gtest.h"
#include "compression.h"
#include <functional>
#include <random>
namespace {
	std::string encode_decode(std::string const &s) {
		std::istringstream in(s);
		std::ostringstream code_out;
		encode(in, code_out);
		std::istringstream code_in(code_out.str());
		std::ostringstream out;
		decode(code_in, out);
		return out.str();
	}

	std::string random_string(std::size_t size) {
		std::string s(size, 0);
		std::random_device r;
		std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
		auto rc = std::bind(std::uniform_int_distribution<>(0, 255), std::mt19937(seed));
		std::generate_n(s.begin(), size, rc);
		return s;
	}
}


TEST(correctness, empty) {
	std::string s;
	EXPECT_EQ(s, encode_decode(s));
}

TEST(correctness, one) {
	std::string s{ '0' };
	EXPECT_EQ(s, encode_decode(s));
}

TEST(correctness, two) {
	std::string s(1, 22);
	EXPECT_EQ(s, encode_decode(s));
}

TEST(correctness, three) {
	std::string s{ 0, 1, 2 };
	EXPECT_EQ(s, encode_decode(s));
}

TEST(correctness, some) {
	std::string s("deadbeaf");
	EXPECT_EQ(s, encode_decode(s));
}

TEST(correctness, short_words) {
	std::string s = "abcd";
	EXPECT_EQ(s, encode_decode(s));
	std::string t = "abcde";
	EXPECT_EQ(t, encode_decode(t));
	std::string h = "abcdef";
	EXPECT_EQ(h, encode_decode(h));
}
TEST(correctness, more_short_words) {
	std::string s = "abcdefg";
	EXPECT_EQ(s, encode_decode(s));
	std::string t = "abcdefgh";
	EXPECT_EQ(t, encode_decode(t));
	std::string h = "abcdefghi";
	EXPECT_EQ(h, encode_decode(h));
}
TEST(correctness, longer_words) {
	std::string t = "abcdefghijk";
	EXPECT_EQ(t, encode_decode(t));

	std::string h = "abcdefghijkl";
	EXPECT_EQ(h, encode_decode(h));

	std::string k = "\xD3\x93Zf\xCA\xF2\xB1" "D\xCB" "d:";
	EXPECT_EQ(k, encode_decode(k));

	std::string s = "abcabcabcabcabc";
	EXPECT_EQ(s, encode_decode(s));
}


TEST(correctness, long_string) {
	std::string s = random_string(100000);
	EXPECT_EQ(s, encode_decode(s));
}

TEST(correctness, random_strings_test) {
	static constexpr std::size_t MAX_LENGTH = 100;
	static constexpr std::size_t REPETITIONS_COUNT = 10;
	for (std::size_t len = 1; len < MAX_LENGTH; ++len) {
		for (std::size_t _ = 0; _ < REPETITIONS_COUNT; ++_) {
			std::string s = random_string(len);
			EXPECT_EQ(s, encode_decode(s));
		}
	}
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
