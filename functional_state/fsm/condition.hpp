#pragma once

#include <functional>

class state;

class condition {
public:
	condition(std::function<bool(state&)> fn);
	bool eval(state& s);
private:
	std::function<bool(state& s)> pred_;
};



