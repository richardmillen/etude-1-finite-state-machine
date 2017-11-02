/////////////////////
// stream_test.cpp //
/////////////////////

#include "stream.hpp"

#include <gtest/gtest.h>

#include <regex>
#include <string>

using namespace std;

const char* STREAM_NAME = "test";

#define NOT_ACCEPT 	0

#define starts_with 	regex_constants::match_continuous
#define ignore_case	regex_constants::icase

TEST(StreamTest, AcceptAll) {
	stream_t all(STREAM_NAME);
	
	EXPECT_EQ(1, all.accept("foo"));
	EXPECT_EQ(1, all.accept("foo\nbar"));
	EXPECT_EQ(1, all.accept(""));
}

TEST(StreamTest, AcceptEmptyString) {
	stream_t empty(STREAM_NAME, "");
	
	EXPECT_EQ(1, empty.accept(""));
	EXPECT_EQ(NOT_ACCEPT, empty.accept("foo"));
}

TEST(StreamTest, NotAcceptString) {
	stream_t foobar(STREAM_NAME, "foo");
	
	EXPECT_EQ(NOT_ACCEPT, foobar.accept("bar")); 
	EXPECT_EQ(NOT_ACCEPT, foobar.accept("foo bar"));
	EXPECT_EQ(NOT_ACCEPT, foobar.accept("you fool"));
	EXPECT_EQ(NOT_ACCEPT, foobar.accept(""));
}

TEST(StreamTest, AcceptString) {
	stream_t foobar(STREAM_NAME, "foo");
	
	EXPECT_EQ(1, foobar.accept("foo")); 
}

TEST(StreamTest, AcceptRegexString) {
	stream_t foobar(STREAM_NAME, "foo|bar");
	
	EXPECT_EQ(1, foobar.accept("foo"));
	EXPECT_EQ(1, foobar.accept("bar"));
}

TEST(StreamTest, AcceptSequence) {
	stream_t seq(STREAM_NAME, {"#", R"(\d+)", "abc"});
	
	EXPECT_EQ(3, seq.accept("#7abc"));
	EXPECT_EQ(3, seq.accept("#1234567abc"));
	
	std::string partial("#7");
	EXPECT_EQ(NOT_ACCEPT, seq.accept(partial));
	
	std::string bad_part1("#!!abc");
	EXPECT_EQ(NOT_ACCEPT, seq.accept(bad_part1));
	
	std::string bad_part2("#7xyz");
	EXPECT_EQ(NOT_ACCEPT, seq.accept(bad_part2));
}



/*
stream_t<T>
-----------

stream_t
--------

stream_t(string name, string match)
stream_t(string name, string[] seq_match)
stream_t(string name) << accept all
string value()
value(string s)

operator<<()
operator=()


*/



////// (TEMPORARY) REGEX EXAMPLES ////// 
TEST(RegexExample, RegexMatch) {
	regex rx("Get|GetValue");
	cmatch m;
	
	EXPECT_TRUE(regex_match("GetValue", m, rx));
	EXPECT_TRUE(regex_match("Get", m, rx));
	EXPECT_FALSE(regex_match("GetValues", m, rx));
}

TEST(RegexExample, RegexMatchString) {
	regex rx("abc");
	string value("abc");
	
	cmatch m;
	EXPECT_TRUE(regex_match(value.c_str(), m, rx));
}

TEST(RegexExample, RegexStartsWith) {
	regex rx("world");
	cmatch m;
	
	EXPECT_EQ(1, regex_search("worldwide", rx, starts_with));
	EXPECT_EQ(0, regex_search("hello world!", rx, starts_with));
}

TEST(RegexExample, RegexIgnoreCase) {
	regex rx("world", ignore_case);
	cmatch m;
	
	EXPECT_TRUE(regex_match("WORLD", m, rx));
}
///////////////////////////



