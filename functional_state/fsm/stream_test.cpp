/////////////////////
// stream_test.cpp //
/////////////////////

#include "stream.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace std;

const char* STREAM_NAME = "test";

#define NOT_ACCEPT 	0

TEST(StreamTest, AcceptAll) {
	stream_t all(STREAM_NAME);
	vector<string> values = {
		"foo",
		"foo\nbar",
		""
	};
	
	for (auto& value : values) {
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
	EXPECT_EQ(NOT_ACCEPT, empty.accept(""));
}

TEST(StreamTest, NotAcceptString) {
	stream_t foobar(STREAM_NAME, "foo");
	EXPECT_EQ(NOT_ACCEPT, foobar.accept("bar"));
}

TEST(StreamTest, NotAcceptWithinString) {
	stream_t foobar(STREAM_NAME, "foo");
	vector<string> values = {
		"foo bar",
		"you fool!"
	};
	
	for (auto& value : values)
		EXPECT_EQ(NOT_ACCEPT, foobar.accept(value));
}

TEST(StreamTest, NotAcceptSubstring) {
	stream_t foobar(STREAM_NAME, "foo");

	EXPECT_EQ(NOT_ACCEPT, foobar.accept("fo"));
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


