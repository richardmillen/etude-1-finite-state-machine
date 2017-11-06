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
public: // consumer api
	context_t();
	bool is_current(state_t& s);
	bool start(state_t& s);
	bool execute(const std::string& input);
public: // event handler api	
	const std::string& input(unsigned seq_index = 0);
	void next_execute(const std::string& input);
public: // state api
	void raise_event(event_t& e);
private:
	void set_current(state_t& s);
	void on_enter_current();
	void on_exit_current();
private:
	state_t* current_;			// TODO: is this safe?
	event_t* raising_;			// TODO: is this safe?
	std::string next_in_;
	bool exec_next_;
};



