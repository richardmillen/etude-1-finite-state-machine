///////////////////
// condition.cpp //
///////////////////

#include "condition.hpp"
#include "state.hpp"

#include <functional>

condition_t::condition_t(std::function<bool(state_t&)> fn) {
	pred_ = fn;
}

bool condition_t::eval(state_t& s) {
	return pred_(s);
}



