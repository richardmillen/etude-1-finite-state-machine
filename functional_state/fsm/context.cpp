/////////////////
// context.cpp //
/////////////////

#include "context.hpp"
#include "state.hpp"

#include <string>
#include <cassert>

context_t::context_t() : current_(NULL)
{}

bool context_t::is_current(state_t& s) {
	return current_ != nullptr && current_->name() == s.name();
}

void context_t::start(state_t& s) {
	current_ = &s;
	s.context_ = this;
}

bool context_t::execute(const std::string& input) {
	assert(current_);
	return current_->execute(input);
}

void context_t::raise_event(event_t& e) {
	raising_ = &e;
	e.raise(*this);
	raising_ = nullptr;
	
	if (!e.has_next())
		return;
	
	start(e.next_state());
}

const std::string& context_t::input(unsigned seq_index) {
	assert(raising_);
	return raising_->stream().accepted(seq_index);
}

