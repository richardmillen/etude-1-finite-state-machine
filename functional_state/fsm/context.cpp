/////////////////
// context.cpp //
/////////////////

#include "context.hpp"

context_t::context_t() : current_(NULL)
{}

bool context_t::is_current(state_t& s) {
	return current_ != nullptr && current_->name() == s.name();
}

void context_t::start(state_t& s) {
	current_ = &s;
}

