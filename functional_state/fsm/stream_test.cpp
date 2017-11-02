/////////////////////
// stream_test.cpp //
/////////////////////

#include "stream.hpp"

#include <gtest/gtest.h>

#include <regex>
#include <string>

using namespace std;

const char* STREAM_NAME = "test";

#define starts_with 	regex_constants::match_continuous
#define ignore_case	regex_constants::icase

TEST(StreamTest, AcceptAll) {
	stream_t all(STREAM_NAME);
	
	EXPECT_EQ(1, all.accept("foo"));
	EXPECT_EQ(1, all.accept("foo\nbar"));
	EXPECT_EQ(1, all.accept(""));
}

TEST(StreamTest, AcceptRegexString) {
	stream_t foobar(STREAM_NAME, "foo|bar");
	
	EXPECT_EQ(1, foobar.accept("foo"));
	EXPECT_EQ(1, foobar.accept("bar"));
	
	EXPECT_EQ(0, foobar.accept("foo bar"));
	EXPECT_EQ(0, foobar.accept("you fool"));
	EXPECT_EQ(0, foobar.accept(""));
}

TEST(StreamTest, AcceptEmptyString) {
	stream_t empty(STREAM_NAME, "");
	
	EXPECT_EQ(1, empty.accept(""));
	EXPECT_EQ(0, empty.accept("foo"));
}

/*TEST(StreamTest, AcceptSequence) {
	stream_t sequence(STREAM_NAME, {"abc", "xyz"});
	
	EXPECT_EQ(empty.accept("foo"));
	EXPECT_EQ(empty.accept(""));
}*/



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



