////////////////
// stream.cpp //
////////////////

#include "stream.hpp"

#include <string>
#include <regex>
#include <cassert>

#define STARTS_WITH	std::regex_constants::match_continuous

const char* MATCH_ALL = R"([\s\S]*)";

stream::stream(const std::string& name)
	: name_(name) {
	matches_.push_back(std::regex(MATCH_ALL));
}

stream::stream(const std::string& name, const std::string& match) 
	: name_(name) {
	matches_.push_back(std::regex(match));
}

stream::stream(const std::string& name, std::initializer_list<std::string> match_seq)
	: name_(name) {
	for (auto& match : match_seq) {
		matches_.push_back(std::regex(match));
	}
}

int stream::accept(const std::string& input) {
	accepted_.clear();
	
	std::cmatch res;
	auto pos = 0u;
	
	for (auto& m : matches_) {
		if (!std::regex_search(input.c_str() + pos, res, m, STARTS_WITH))
			return 0;
		accepted_.push_back(res[0]);
		pos += accepted_.back().size();
	}
	
	if (pos != input.size())
		return 0;

	return accepted_.size();
}

const std::string& stream::accepted(unsigned seq_index) {
	assert(seq_index < accepted_.size());
	return accepted_[seq_index];
}



