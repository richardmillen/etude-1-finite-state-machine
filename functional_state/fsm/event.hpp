///////////////
// event.hpp //
///////////////

#pragma once

#include <functional>
#include <initializer_list>
#include <vector>

class context_t;
class state_t;
class stream_t;

class event_t {
public:
	event_t(stream_t& in, std::function<void(context_t&)> fn);
	stream_t& stream();
	void raise(context_t& ctx);
	void next_state(state_t& s);
	void next_state(std::initializer_list<std::reference_wrapper<state_t>> s);
	void must_next(state_t& s);
	void must_next(std::initializer_list<std::reference_wrapper<state_t>> s);
	state_t* next_state();
private:
	stream_t& in_;
	std::function<void(context_t&)> handler_;
	std::vector<std::reference_wrapper<state_t>> next_states_;
	bool must_;
};



