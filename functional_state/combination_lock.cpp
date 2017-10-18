//////////////////////////
// combination_lock.cpp //
//////////////////////////

#include "fsm/context.hpp"

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char* argv[]) {
	context_t lock;
	
	vector<condition_t> combo = {1, 2, 1, 2}; 
	vector<condition_t> dials = {0, 0, 0, 0};
	
	state_t locked("locked");
	state_t unlocked("unlocked");
	state_t open("open");
	
	stream_t cmd_open("open", "open");
	stream_t cmd_close("close", "close");
	stream_t cmd_up("up", "up");
	stream_t cmd_down("down", "down");
	
	locked.add_condition(dials, condition_t::not_equal_to(), combo);
	unlocked.add_condition(dials, condition_t::equal_to(), combo);
	
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
	assert(locked.is_current());
	
	lock.send("open");			// <--- ignored
	lock.send("close");			// <--- ignored
	
			//      0, 0, 0, 0 (initial position)
	up(0);		// <--- [1], 0, 0, 0
	up(1);		// <--- 1, [1], 0, 0
	up(1);		// <--- 1, [2], 0, 0
	up(2);		// <--- 1, 2, [1], 0
	up(3);		// <--- 1, 2, 1, [1]
	up(3);		// <--- 1, 2, 1, [2] (unlocked position)
	
	assert(lock.is_current(unlocked));
	assert(unlocked.is_current());
	
	down(3);	// <--- 1, 2, 1, [1] (locked again)
	
	assert(lock.is_current(locked));
	assert(locked.is_current());
	
	up(3);		// <--- 1, 2, 1, [2] (unlocked again)
	
	assert(lock.is_current(unlocked));
	assert(unlocked.is_current());
	
	open();
	
	assert(lock.is_current(open));
	assert(open.is_current());
	
	down(0);	// <--- [0], 2, 1, 2 (locked position, though still open!)
	
	assert(lock.is_current(open));
	assert(open.is_current());
	
	close();
	
	assert(lock.is_current(locked));
	assert(locked.is_current());
	
	open();		// <--- ignored 
	
	up(0);		// <--- [1], 2, 1, 2 (unlocked position)
	
	lock.execute("open");
	
	assert(lock.is_current(open));
	assert(open.is_current());
	
	lock.execute("close");
	
	assert(lock.is_current(unlocked));
	assert(unlocked.is_current());
	
	close()		// <--- ignored
	
	return 0;
}











