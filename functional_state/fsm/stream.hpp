////////////////
// stream.hpp //
////////////////

#pragma once

#include <initializer_list>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

class stream_t {
public:
	stream_t(const std::string& name);
	stream_t(const std::string& name, const std::string& match);
	stream_t(const std::string& name, std::initializer_list<std::string> match_seq);
	int accept(const std::string& input);
	std::vector<std::string>& accepted();
private:
	std::string name_;
	std::vector<std::regex> matches_;
	std::vector<std::string> accepted_;
};

