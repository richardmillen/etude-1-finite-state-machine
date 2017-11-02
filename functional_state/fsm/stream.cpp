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
}

stream_t::stream_t(const std::string& name, const std::string& match) 
	: name_(name) {
	matches_.push_back(std::regex(match));
}

stream_t::stream_t(const std::string& name, std::initializer_list<std::string> match_seq)
	: name_(name) {
	for (auto& match : match_seq) {
		matches_.push_back(std::regex(match));
	}
}

int stream_t::accept(const std::string& input) {
	accepted_.clear();
	
	std::cmatch res;
	auto pos = 0u;
	
	for (m : matches_) {
		if (!std::regex_search(input.c_str() + pos, res, m, STARTS_WITH))
			return 0;
		accepted_.push_back(res[0]);
		pos += accepted_.back().size();
	}
	
	if (pos != input.size())
		return 0;

	return accepted_.size();
}

std::vector<std::string>& stream_t::accepted() {
	return accepted_;
}



