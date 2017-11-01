/////////////////////
// stream_test.cpp //
/////////////////////

#include "stream.hpp"

#include <gtest/gtest.h>

#include <regex>
#include <string>

#define starts_with 	std::regex_constants::match_continuous
#define ignore_case	std::regex_constants::icase

TEST(StreamTest, EmptyMatchString) {
	stream_t foo("name", "");
	
	EXPECT_FALSE(foo.match("foo"));
	EXPECT_TRUE(foo.match(""));
}



/*
stream_t<T>
-----------

stream_t
--------

stream_t(string name, string match)
stream_t(string name, string introducer, string input)
std::string value()
value(std::string s)

operator<<()
operator=()


*/



////// REGEX SAMPLES ////// 
TEST(RegexTest, RegexMatch) {
	std::regex rx("Get|GetValue");
	std::cmatch m;
	
	EXPECT_TRUE(std::regex_match("GetValue", m, rx));
	EXPECT_TRUE(std::regex_match("Get", m, rx));
	EXPECT_FALSE(std::regex_match("GetValues", m, rx));
}

TEST(RegexTest, RegexMatchString) {
	std::regex rx("abc");
	std::string value("abc");
	
	std::cmatch m;
	EXPECT_TRUE(std::regex_match(value.c_str(), m, rx));
}

TEST(RegexTest, RegexStartsWith) {
	std::regex rx("world");
	std::cmatch m;
	
	EXPECT_EQ(1, std::regex_search("worldwide", rx, starts_with));
	EXPECT_EQ(0, std::regex_search("hello world!", rx, starts_with));
}

TEST(RegexTest, RegexIgnoreCase) {
	std::regex rx("world", ignore_case);
	std::cmatch m;
	
	EXPECT_TRUE(std::regex_match("WORLD", m, rx));
}
///////////////////////////



