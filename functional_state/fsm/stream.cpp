////////////////
// stream.cpp //
////////////////

#include "stream.hpp"

#include <string>
#include <regex>

#define STARTS_WITH	std::regex_constants::match_continuous

const char* MATCH_ALL = R"([\s\S]*)";

stream_t::stream_t(const std::string& name)
	: name_(name), match_(MATCH_ALL) {
	
}

stream_t::stream_t(const std::string& name, const std::string& match) 
	: name_(name), match_(match)
{}

int stream_t::accept(const std::string& input) {
	std::cmatch results;
	auto c = std::regex_search(input.c_str(), results, match_, STARTS_WITH);
	if (c == 0)
		return 0;
	if (input != results[0])
		return 0;
	return 1;
}

std::vector<std::ostringstream>& stream_t::accepted() {
	return accepted_;
}
