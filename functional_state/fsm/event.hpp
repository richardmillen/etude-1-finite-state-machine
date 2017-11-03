///////////////
// event.hpp //
///////////////

#pragma once

#include <functional>

class stream_t;

class event_t {
public:
	event_t(stream_t& in, std::function<void()> fn);
	stream_t& stream();
	void raise();
private:
	stream_t& in_;
	std::function<void()> handler_;
};



