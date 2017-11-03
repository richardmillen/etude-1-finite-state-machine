///////////////
// event.cpp //
///////////////

#include "event.hpp"

event_t::event_t(stream_t& in, std::function<void()> fn) 
	: in_(in), handler_(fn) {
}

stream_t& event_t::stream() {
	return in_;
}

void event_t::raise() {
	handler_();
}

