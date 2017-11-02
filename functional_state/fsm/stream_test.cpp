/////////////////////
// stream_test.cpp //
/////////////////////

#include "stream.hpp"

#include <gtest/gtest.h>

#include <regex>
#include <string>
#include <vector>

using namespace std;

const char* STREAM_NAME = "test";

#define NOT_ACCEPT 	0

#define starts_with 	regex_constants::match_continuous
#define ignore_case	regex_constants::icase

TEST(StreamTest, AcceptAll) {
	stream_t all(STREAM_NAME);
	vector<string> values = {
		"foo",
		"foo\nbar",
		""
	};
	
	for (value : values) {
		EXPECT_EQ(1, all.accept(value));
		EXPECT_EQ(value, all.accepted());
	}
}

TEST(StreamTest, AcceptEmptyString) {
	stream_t empty(STREAM_NAME, "");
	
	EXPECT_EQ(1, empty.accept(""));
	EXPECT_EQ("", empty.accepted());
}

TEST(StreamTest, NotAcceptEmptyString) {
	stream_t empty(STREAM_NAME, "foo");
	EXPECT_EQ(0, empty.accept(""));
}

TEST(StreamTest, NotAcceptString) {
	stream_t foobar(STREAM_NAME, "foo");
	EXPECT_EQ(0, foobar.accept("bar"));
}

TEST(StreamTest, NotAcceptWithinString) {
	stream_t foobar(STREAM_NAME, "foo");
	vector<string> values = {
		"foo bar",
		"you fool!"
	};
	
	for (value : values)
		EXPECT_EQ(0, foobar.accept(value));
}

TEST(StreamTest, NotAcceptSubstring) {
	stream_t foobar(STREAM_NAME, "foo");

	EXPECT_EQ(0, foobar.accept("fo"));
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

TEST(StreamTest, AcceptSimpleSequence) {
	stream_t seq(STREAM_NAME, {"a", "b", "c"});
	
	EXPECT_EQ(3, seq.accept("abc"));
}

TEST(StreamTest, NotAcceptSequence) {
	stream_t seq(STREAM_NAME, {"1", "2", "3"});
	
	EXPECT_EQ(NOT_ACCEPT, seq.accept("12"));
	EXPECT_EQ(NOT_ACCEPT, seq.accept("129"));
	EXPECT_EQ(NOT_ACCEPT, seq.accept("456"));
	EXPECT_EQ(NOT_ACCEPT, seq.accept(""));
}

TEST(StreamTest, AcceptComplexSequence) {
	stream_t seq(STREAM_NAME, {"#|!", R"(\d+)", "[abc]{3}"});
	
	EXPECT_EQ(3, seq.accept("#7abc"));
	EXPECT_EQ(3, seq.accept("!1234567cba"));
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



