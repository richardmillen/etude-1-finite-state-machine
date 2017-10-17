///////////////
// timer.cpp //
///////////////

#include "fsm/context.hpp"

#include <iostream>
#include <functional>
#include <chrono>

int main(int argc, char* argv[]) {
	context_t clock;
	
	auto count = clock.add_condition("counter", 10);
	
	auto timer = clock.add_timer("timer", [&]() {
		auto c = count.writeable();
		cout << "timer: " << c-- << endl;
	}).interval(1s);
	
	auto bell = clock.add_timer("bell", []() {
		cout << "alarm: ding-a-ling!" << endl;
	}).interval(500ms);
	
	auto on = clock.add_initial_state("on");
	
	auto start = on.add_command(equal_to("start"), [&]() {
		timer.start();
	});
	
	on.add_substate("alarm", count, less_equal(), 0)
	alarm.on_enter([&]() {
		cout << "alarm: starting alarm..." << endl;
		bell.start();
	});
	
	start();
	
	return 0;
}











