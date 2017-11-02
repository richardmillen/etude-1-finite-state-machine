////////////////
// stream.cpp //
////////////////

#include "stream.hpp"

#include <string>
#include <regex>

const char* MATCH_ALL = R"([\s\S]*)";

stream_t::stream_t(const std::string& name)
	: name_(name), match_(MATCH_ALL)
{}

stream_t::stream_t(const std::string& name, const std::string& match) 
	: name_(name), match_(match)
{}

bool stream_t::accept(const std::string& input) {
	std::cmatch m;
	return std::regex_match(input.c_str(), m, match_);
}

