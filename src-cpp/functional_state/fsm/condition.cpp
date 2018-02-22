///////////////////
// condition.cpp //
///////////////////

#include "condition.hpp"
#include "state.hpp"

#include <functional>

condition::condition(std::function<bool(state&)> fn) {
	pred_ = fn;
}

bool condition::eval(state& s) {
	return pred_(s);
}



