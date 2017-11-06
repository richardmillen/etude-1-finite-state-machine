///////////////
// state.cpp //
///////////////

#include "state.hpp"
#include "context.hpp"
#include "event.hpp"

#include <string>
#include <cassert>

state_t::state_t(const std::string& name) 
	: name_(name), parent_(nullptr) {
}

const std::string& state_t::name() {
	return name_;
}

event_t& state_t::on_event(stream_t& in, std::function<void(context_t&)> handler) {
	events_.push_back(event_t(in, handler));
	return events_.back();
}

state_t& state_t::add_substate(state_t& s) {
	assert(s.parent_ == nullptr);
	s.parent_ = this;
	return s;
}

void state_t::add_condition(condition_t& c) {
	conditions_.push_back(c);
}

void state_t::add_condition(condition_t&& c) {
	conditions_.push_back(c);
}

void state_t::on_enter(std::function<void(context_t&)> handler) {
	enter_ = handler;
}

void state_t::on_exit(std::function<void(context_t&)> handler) {
	exit_ = handler;
}

bool state_t::execute(const std::string& input) {
	assert(context_);
	
	for (auto& e : events_) {
		if (e.stream().accept(input) > 0) {
			context_->raise_event(e);
			return true;
		}
	}
	
	if (!parent_)
		return false;
	
	return parent_->execute(input);
}

bool state_t::can_enter() {
	for (auto& c : conditions_) {
		if (!c.eval(*this))
			return false;
	}
	return true;
}










