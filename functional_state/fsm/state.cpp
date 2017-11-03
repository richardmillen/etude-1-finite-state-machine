///////////////
// state.cpp //
///////////////

#include "state.hpp"
#include "context.hpp"
#include "event.hpp"

#include <string>

state_t::state_t(const std::string& name) : name_(name)
{}

const std::string& state_t::name() {
	return name_;
}

event_t& state_t::on_event(stream_t& in, std::function<void()> handler) {
	events_.push_back(event_t(in, handler));
	return events_.back();
}

bool state_t::execute(const std::string& input) {
	for (auto& e : events_) {
		if (e.stream().accept(input) > 0) {
			e.raise();
			return true;
		}
	}
	return false;
}


