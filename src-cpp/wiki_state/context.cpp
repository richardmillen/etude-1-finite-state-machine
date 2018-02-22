#include "context.hpp"
#include "state.hpp"
#include "lowercase.hpp"

#include <string>
using namespace std;

context_t::context_t() {
	set(new lowercase_t());
}

void context_t::set(state_t* state) {
	state_.reset(state);
}

void context_t::write(const string& name) {
	state_->write(*this, name);
}

