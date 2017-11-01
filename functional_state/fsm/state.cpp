///////////////
// state.cpp //
///////////////

#include "state.hpp"

#include <string>

state_t::state_t(const std::string& name) : name_(name)
{}

std::string& state_t::name() {
	return name_;
}
