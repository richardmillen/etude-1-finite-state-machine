///////////////
// event.hpp //
///////////////

#pragma once

#include <functional>
#include <initializer_list>
#include <vector>

class context;
class state;
class stream;

class event {
public:
	event(stream& in, std::function<void(context&)> fn);
	stream& stream();
	void raise(context& ctx);
	void next_state(state& s);
	void next_state(std::initializer_list<std::reference_wrapper<state>> s);
	void must_next(state& s);
	void must_next(std::initializer_list<std::reference_wrapper<state>> s);
	state* next_state();
private:
	stream& in_;
	std::function<void(context&)> handler_;
	std::vector<std::reference_wrapper<state>> next_states_;
	bool must_;
};



