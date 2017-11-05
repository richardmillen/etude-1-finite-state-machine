///////////////
// event.cpp //
///////////////

#include "event.hpp"

#include <cassert>

event_t::event_t(stream_t& in, std::function<void(context_t&)> fn) 
	: in_(in), handler_(fn), next_(nullptr) {
}

stream_t& event_t::stream() {
	return in_;
}

void event_t::raise(context_t& ctx) {
	handler_(ctx);
}

void event_t::next_state(state_t& s) {
	next_ = &s;
}

state_t& event_t::next_state() {
	assert(next_);
	return *next_;
}

bool event_t::has_next() {
	return next_ != nullptr;
}



