////////////////
// stream.hpp //
////////////////

#pragma once

#include <initializer_list>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

class stream {
public:
	stream(const std::string& name);
	stream(const std::string& name, const std::string& match);
	stream(const std::string& name, std::initializer_list<std::string> match_seq);
	int accept(const std::string& input);
	const std::string& accepted(unsigned seq_index = 0);
private:
	std::string name_;
	std::vector<std::regex> matches_;
	std::vector<std::string> accepted_;
};




