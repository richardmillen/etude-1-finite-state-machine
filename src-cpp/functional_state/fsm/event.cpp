///////////////
// event.cpp //
///////////////

#include "event.hpp"
#include "state.hpp"

#include <cassert>
#include <functional>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

using namespace std;

event::event(stream& in, std::function<void(context&)> fn) 
	: in_(in), handler_(fn), must_(false) {
}

stream& event::stream() {
	return in_;
}

void event::raise(context& ctx) {
	handler_(ctx);
}

void event::next_state(state& s) {
	next_states_.push_back(s);
}

void event::next_state(initializer_list<reference_wrapper<state>> s) {
	next_states_.insert(next_states_.end(), s.begin(), s.end());
}

void event::must_next(state& s) {
	must_ = true;
	next_states_.push_back(s);
}

void event::must_next(std::initializer_list<std::reference_wrapper<state>> s) {
	must_ = true;
	next_states_.insert(next_states_.end(), s.begin(), s.end());
}

state* event::next_state() {
	auto it = find_if(next_states_.begin(), next_states_.end(), 
			  [](const reference_wrapper<state>& s) {
		return s.get().can_enter();
	});
	if (it != next_states_.end())
		return &((*it).get());
	if (must_)
		throw std::logic_error("failed to move to next state");
	return nullptr;
}

	





