/////////////////
// context.cpp //
/////////////////

#include "context.hpp"
#include "state.hpp"

#include <string>
#include <cassert>

context::context() : current_(nullptr), raising_(nullptr)
{}

bool context::is_current(state& s) {
	return current_ != nullptr && current_->name() == s.name();
}

bool context::start(state& s) {
	if (!s.can_enter())
		return false;
	
	on_exit_current();
	set_current(s);
	on_enter_current();
	
	return true;
}

bool context::execute(const std::string& input) {
	assert(current_);
	return current_->execute(input);
}

void context::raise_event(event& e) {
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

const std::string& context::input(unsigned seq_index) {
	assert(raising_);
	return raising_->stream().accepted(seq_index);
}

void context::next_execute(const std::string& input) {
	exec_next_ = true;
	next_in_.assign(input);
}

void context::set_current(state& s) {
	current_ = &s;
	s.context_ = this;
}

void context::on_exit_current() {
	if (!current_)
		return;
	if (!current_->exit_)
		return;
	current_->exit_(*this);
}

void context::on_enter_current() {
	if (!current_)
		return;
	if (!current_->enter_)
		return;
	current_->enter_(*this);
}	





