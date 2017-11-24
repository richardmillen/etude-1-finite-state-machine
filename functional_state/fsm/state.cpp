///////////////
// state.cpp //
///////////////

#include "state.hpp"
#include "context.hpp"
#include "event.hpp"

#include <string>
#include <cassert>

state::state(const std::string& name) 
	: name_(name), parent_(nullptr) {
}

const std::string& state::name() {
	return name_;
}

event& state::on_event(stream& in, std::function<void(context&)> handler) {
	events_.push_back(event(in, handler));
	return events_.back();
}

state& state::add_substate(state& s) {
	assert(s.parent_ == nullptr);
	s.parent_ = this;
	return s;
}

void state::add_condition(condition& c) {
	conditions_.push_back(c);
}

void state::add_condition(condition&& c) {
	conditions_.push_back(c);
}

void state::on_enter(std::function<void(context&)> handler) {
	enter_ = handler;
}

void state::on_exit(std::function<void(context&)> handler) {
	exit_ = handler;
}

bool state::execute(const std::string& input) {
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

bool state::can_enter() {
	for (auto& c : conditions_) {
		if (!c.eval(*this))
			return false;
	}
	return true;
}










