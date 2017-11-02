/////////////////
// context.hpp //
/////////////////

#pragma once

#include "state.hpp"

#include <memory>

class context_t {
public:
	context_t();
	bool is_current(state_t& s);
	void start(state_t& s);
private:
	state_t* current_;			// TODO: is this safe?
};



