///////////////
// event.cpp //
///////////////

#include "event.hpp"
#include "state.hpp"

#include <cassert>
#include <functional>
#include <initializer_list>
#include <algorithm>

using namespace std;

event_t::event_t(stream_t& in, std::function<void(context_t&)> fn) 
	: in_(in), handler_(fn) {
}

stream_t& event_t::stream() {
	return in_;
}

void event_t::raise(context_t& ctx) {
	handler_(ctx);
}

void event_t::next_state(state_t& s) {
	next_states_.push_back(s);
}

void event_t::next_state(initializer_list<reference_wrapper<state_t>> s) {
	next_states_.insert(next_states_.end(), s.begin(), s.end());
}

state_t* event_t::next_state() {
	auto it = find_if(next_states_.begin(), next_states_.end(), 
			  [](const reference_wrapper<state_t>& s) {
		return s.get().can_enter();
	});
	if (it == next_states_.end())
		return nullptr;
	return &((*it).get());
	
	auto& s = (*it).get();
	return &s;
}



