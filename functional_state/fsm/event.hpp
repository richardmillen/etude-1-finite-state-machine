///////////////
// event.hpp //
///////////////

#pragma once

#include <functional>

class context_t;
class stream_t;

class event_t {
public:
	event_t(stream_t& in, std::function<void(context_t&)> fn);
	stream_t& stream();
	void raise(context_t& ctx);
private:
	stream_t& in_;
	std::function<void(context_t&)> handler_;
};



