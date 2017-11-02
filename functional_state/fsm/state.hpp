///////////////
// state.hpp //
///////////////

#pragma once

#include <string>

class state_t {
public:
	state_t(const std::string& name);
	const std::string& name();
private:
	std::string name_;
};



