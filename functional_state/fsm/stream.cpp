////////////////
// stream.cpp //
////////////////

#include "stream.hpp"

#include <string>
#include <regex>

#define STARTS_WITH	std::regex_constants::match_continuous

const char* MATCH_ALL = R"([\s\S]*)";

stream_t::stream_t(const std::string& name)
	: name_(name) {
	matches_.push_back(std::regex(MATCH_ALL));
	accepted_.push_back(std::string());
}

stream_t::stream_t(const std::string& name, const std::string& match) 
	: name_(name) {
	matches_.push_back(std::regex(match));
	accepted_.push_back(std::string());
}

stream_t::stream_t(const std::string& name, std::initializer_list<std::string> match_seq)
	: name_(name) {
	for (auto& match : match_seq) {
		matches_.push_back(std::regex(match));
		accepted_.push_back(std::string());
	}
}

int stream_t::accept(const std::string& input) {
	std::cmatch results;
	auto c = std::regex_search(input.c_str(), results, matches_[0], STARTS_WITH);
	if (c == 0)
		return 0;
	if (input != results[0])
		return 0;
	return 1;
}

std::vector<std::string>& stream_t::accepted() {
	return accepted_;
}



