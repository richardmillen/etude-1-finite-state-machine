/////////////////
// context.cpp //
/////////////////

#include "context.hpp"
#include "state.hpp"

#include <string>
#include <cassert>

context_t::context_t() : current_(nullptr), raising_(nullptr)
{}

bool context_t::is_current(state_t& s) {
	return current_ != nullptr && current_->name() == s.name();
}

void context_t::start(state_t& s) {
	if (current_ && current_->exit_)
		current_->exit_(*this);
	
	current_ = &s;
	s.context_ = this;
	
	if (!s.enter_)
		return;
	
	s.enter_(*this);
}

bool context_t::execute(const std::string& input) {
	assert(current_);
	return current_->execute(input);
}

void context_t::raise_event(event_t& e) {
	exec_next_ = false;
	
	raising_ = &e;
	e.raise(*this);
	raising_ = nullptr;
	
	if (!e.has_next())
		return;
	
	start(e.next_state());
	
	if (!exec_next_)
		return;
	
	execute(next_in_);
}

const std::string& context_t::input(unsigned seq_index) {
	assert(raising_);
	return raising_->stream().accepted(seq_index);
}

void context_t::next_execute(const std::string& input) {
	exec_next_ = true;
	next_in_.assign(input);
}





