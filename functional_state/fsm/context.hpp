/////////////////
// context.hpp //
/////////////////

#pragma once

#include <string>
#include <memory>

class state;
class stream;
class event;

class context {
public: // consumer api
	context();
	bool is_current(state& s);
	bool start(state& s);
	bool execute(const std::string& input);
public: // event handler api	
	const std::string& input(unsigned seq_index = 0);
	void next_execute(const std::string& input);
public: // state api
	void raise_event(event& e);
private:
	void set_current(state& s);
	void on_enter_current();
	void on_exit_current();
private:
	state* current_;			// TODO: is this safe?
	event* raising_;			// TODO: is this safe?
	std::string next_in_;
	bool exec_next_;
};



