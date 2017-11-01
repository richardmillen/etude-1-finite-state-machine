////////////////
// stream.cpp //
////////////////

#include "stream.hpp"

#include <string>
#include <regex>

stream_t::stream_t(const std::string& name, const std::string& match) 
	: name_(name), match_(match)
{}

bool stream_t::match(const std::string& input) {
	std::cmatch m;
	return std::regex_match(input.c_str(), m, match_);
}

