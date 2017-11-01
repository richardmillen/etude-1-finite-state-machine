////////////////
// stream.hpp //
////////////////

#pragma once

#include <string>
#include <regex>

class stream_t {
public:
	stream_t(const std::string& name, const std::string& match);
	bool match(const std::string& input);
private:
	std::string name_;
	std::regex match_;
};

