/////////////////
// context.hpp //
/////////////////

#pragma once

#include <string>
#include <memory>

class state_t;
class stream_t;
class event_t;

class context_t {
public:
	context_t();
	bool is_current(state_t& s);
	void start(state_t& s);
	bool execute(const std::string& input);
	void raise_event(event_t& e);
	stream_t& input();
private:
	state_t* current_;			// TODO: is this safe?
	event_t* raising_;			// TODO: is this safe?
};



