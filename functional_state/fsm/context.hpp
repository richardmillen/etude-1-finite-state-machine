/////////////////
// context.hpp //
/////////////////

#pragma once

#include <string>
#include <memory>

class state_t;

class context_t {
public:
	context_t();
	bool is_current(state_t& s);
	void start(state_t& s);
	bool execute(const std::string& input);
private:
	state_t* current_;			// TODO: is this safe?
};



