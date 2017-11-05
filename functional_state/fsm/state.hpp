///////////////
// state.hpp //
///////////////

#pragma once

#include "stream.hpp"
#include "event.hpp"

#include <string>
#include <vector>
#include <functional>

class context_t;

class state_t {
	friend class context_t;
public:
	state_t(const std::string& name);
	const std::string& name();
	event_t& on_event(stream_t& in, std::function<void(context_t&)> handler);
	void on_enter(std::function<void(context_t&)> handler);
	bool execute(const std::string& input);
private:
	context_t* context_;			// TODO: is this safe?
	std::string name_;
	std::vector<event_t> events_;
	std::function<void(context_t&)> enter_handler_;
};



