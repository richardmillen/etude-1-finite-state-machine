#pragma once

#include "state.hpp"

#include <string>
#include <memory>

class context_t {
public:
	context_t();
	void set(state_t* state);
	void write(const std::string& name);
private:
	std::unique_ptr<state_t> state_;
};
