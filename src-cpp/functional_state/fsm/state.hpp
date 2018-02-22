///////////////
// state.hpp //
///////////////

#pragma once

#include "stream.hpp"
#include "event.hpp"
#include "condition.hpp"

#include <string>
#include <vector>
#include <functional>

class context;

class state {
	friend class context;
public:
	state(const std::string& name);
	const std::string& name();
	event& on_event(stream& in, std::function<void(context&)> handler);
	state& add_substate(state& s);
	void add_condition(condition& c);
	void add_condition(condition&& c);
	void on_enter(std::function<void(context&)> handler);
	void on_exit(std::function<void(context&)> handler);
	bool execute(const std::string& input);
	bool can_enter();
private:
	context* context_;			// TODO: is this safe?
	std::string name_;
	state* parent_;
	std::vector<event> events_;
	std::vector<condition> conditions_;
	std::function<void(context&)> enter_;
	std::function<void(context&)> exit_;
};



