#pragma once

#include <string>

class state_t {
public:
	~state_t() {}
	virtual void write(class context_t& context, const std::string& name) = 0;
};
