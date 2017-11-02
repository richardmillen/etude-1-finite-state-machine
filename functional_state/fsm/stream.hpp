////////////////
// stream.hpp //
////////////////

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <regex>

class stream_t {
public:
	stream_t(const std::string& name);
	stream_t(const std::string& name, const std::string& match);
	int accept(const std::string& input);
	std::vector<std::ostringstream>& accepted();
private:
	std::string name_;
	std::regex match_;
	std::vector<std::ostringstream> accepted_;
};

