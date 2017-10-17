#pragma once

#include "state.hpp"
#include "context.hpp"

#include <string>

class multiupper_t : public state_t {
public:
	virtual void write(context_t& context, const std::string& name) override;
private:
	int count_ = 0;
};
