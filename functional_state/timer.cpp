///////////////
// timer.cpp //
///////////////

#include "fsm/context.hpp"

#include <iostream>
#include <functional>
#include <chrono>

int main(int argc, char* argv[]) {
	context_t clock;
	
	stream_t<int> count("counter", 10);
	stream_t start("start", "start");
	
	condition_t timed_out([]() {
		// TODO: how best to implement?	
	});
	
	timer_t timer("timer", 1s);
	timer_t bell("bell", 500ms);
	
	state_t on("on", timer);
	state_t alarm("alarm", bell);
	
	on.add_substate(alarm);
	
	on.on_event(start, [](ctx) {
		cout << "starting timer..."	
		ctx.start_timer();
	});
	
	timer.on_tick(count, [](ctx) {
		cout << "timer: " << ctx.value()-- << endl;
	}).next_state(timed_out, alarm);
	
	bell.on_tick([](ctx) {
		cout << "alarm: ding-a-ling!" << endl;
	});
	
	alarm.on_enter([](ctx) {
		ctx.start_timer();	
	});
	
	clock.initial_state(on);
	
	clock.send("start");
	
	return 0;
}











