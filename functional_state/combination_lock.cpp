//////////////////////////
// combination_lock.cpp //
//////////////////////////

#include "fsm/context.hpp"

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char* argv[]) {
	context lock;
	
	vector<condition> combo = {1, 2, 1, 2}; 
	vector<condition> dials = {0, 0, 0, 0};
	
	state locked("locked");
	state unlocked("unlocked");
	state open("open");
	
	stream cmd_open("open", "open");
	stream cmd_close("close", "close");
	stream cmd_up("up", "u", "[1234]");
	stream cmd_down("down", "d", "[1234]");
	
	locked.add_condition(dials, condition::not_equal_to(), combo);
	unlocked.add_condition(dials, condition::equal_to(), combo);
	
	UP: 
		auto w = dials.writeable();
		++w[i];
	
	DOWN:
		auto w = dials.writeable();
		--w[i];
		
	locked.on_enter([]() {
		cout << "entering locked state..." << endl;
	});
	locked.on_exit([]() {
		cout << "leaving locked state..." << endl;
	});
	
	unlocked.on_enter([]() {
		cout << "entering unlocked state..." << endl;
	});
	unlocked.on_event(cmd_open, [](ctx) {
		cout << "opening lock..." << endl;
	}).next_state(open);;
	unlocked.on_exit([]() {
		cout << "leaving unlocked state..." << endl;
	});
	
	open.on_enter([]() {
		cout << "entering open state..." << endl;
	});
	open.on_event(cmd_close, [](ctx) {
		cout << "closing lock..." << endl;
	});
	open.on_exit([]() {
		cout << "leaving open state..." << endl;
	});
	
	lock.initial_state({locked, unlocked});
	
	assert(lock.is_current(locked))
	
	lock.send("open");			// <--- ignored
	lock.send("close");			// <--- ignored
	
				//      0, 0, 0, 0 (initial position)
	lock.send("u0");	// <--- [1], 0, 0, 0
	lock.send("u1");	// <--- 1, [1], 0, 0
	lock.send("u1");	// <--- 1, [2], 0, 0
	lock.send("u2");	// <--- 1, 2, [1], 0
	lock.send("u3");	// <--- 1, 2, 1, [1]
	lock.send("u3");	// <--- 1, 2, 1, [2] (unlocked position)
	
	assert(lock.is_current(unlocked));
	
	lock.send("d3");	// <--- 1, 2, 1, [1] (locked again)
	
	assert(lock.is_current(locked));
	
	lock.send("u3");		// <--- 1, 2, 1, [2] (unlocked again)
	
	assert(lock.is_current(unlocked));
	
	lock.send("open");
	
	assert(lock.is_current(open));
	
	lock.send("u0");	// <--- [0], 2, 1, 2 (locked position, though still open!)
	
	assert(lock.is_current(open));
	
	lock.send("close");
	
	assert(lock.is_current(locked));
	
	lock.send("open");		// <--- ignored 
	
	lock.send("u0");		// <--- [1], 2, 1, 2 (unlocked position)
	
	lock.send("open");
	
	assert(lock.is_current(open));
	
	lock.send("close");
	
	assert(lock.is_current(unlocked));
	
	lock.send("close");		// <--- ignored
	
	return 0;
}











