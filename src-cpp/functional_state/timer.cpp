///////////////
// timer.cpp //
///////////////

#include "fsm/context.hpp"

#include <iostream>
#include <functional>
#include <chrono>

int main(int argc, char* argv[]) {
	context clock;
	
	stream<int> count("counter", 10);
	stream start("start", "start");
	
	condition timed_out([]() {
		// TODO: how best to implement?	
	});
	
	timer timer("timer", 1s);
	timer bell("bell", 500ms);
	
	state on("on", timer);
	state alarm("alarm", bell);
	
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











