#pragma once

#include "state.hpp"
#include "context.hpp"

#include <string>

class lowercase_t : public state_t {
public:
	virtual void write(context_t& context, const std::string& name) override;
};
