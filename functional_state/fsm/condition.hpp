#pragma once

#include <functional>

class state_t;

class condition_t {
public:
	condition_t(std::function<bool(state_t&)> fn);
	bool eval(state_t& s);
private:
	std::function<bool(state_t& s)> pred_;
};



