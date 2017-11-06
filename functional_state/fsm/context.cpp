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

bool context_t::start(state_t& s) {
	if (!s.can_enter())
		return false;
	
	on_exit_current();
	set_current(s);
	on_enter_current();
	
	return true;
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
	
	auto next = e.next_state();
	if (!next)
		return;
	
	if (!start(*next))
		return;
	
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

void context_t::set_current(state_t& s) {
	current_ = &s;
	s.context_ = this;
}

void context_t::on_exit_current() {
	if (!current_)
		return;
	if (!current_->exit_)
		return;
	current_->exit_(*this);
}

void context_t::on_enter_current() {
	if (!current_)
		return;
	if (!current_->enter_)
		return;
	current_->enter_(*this);
}	





