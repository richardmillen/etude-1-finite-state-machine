//////////////////////////
// combination_lock.cpp //
//////////////////////////

#include "fsm/context.hpp"

#include <iostream>
#include <functional>

int main(int argc, char* argv[]) {
	context_t lock;
	
	lock.conditions["combination"]    = [1, 2, 1, 2];
	lock.conditions["dial-positions"] = [0, 0, 0, 0];
	
	auto dials = lock.conditions["dial-positions"];
	auto unlock_pos = lock.conditions["combination"];
	
	auto locked = lock.add_state("locked", dials, not_equal_to(unlock_pos));
	locked.on_enter([]() {
		cout << "entering locked state..." << endl;
	});
	locked.on_exit([]() {
		cout << "leaving locked state..." << endl;
	});
	
	auto unlocked = lock.add_state("unlocked", dials, equal_to(unlock_pos));
	unlocked.on_enter([]() {
		cout << "entering unlocked state..." << endl;
	});
	unlocked.on_exit([]() {
		cout << "leaving unlocked state..." << endl;
	});
	
	auto open = unlocked.add_state("open"); 
	open.on_enter([]() {
		cout << "entering open state..." << endl;
	});
	open.on_exit([]() {
		cout << "leaving open state..." << endl;
	});
	
	auto close = open.add_command("close", []() {
		cout << "closing lock..." << endl;
	}).next_state({locked, unlocked});
	
	auto up = lock.add_command("spin-up", [&](i) {
		auto w = dials.writeable();
		++w[i];
	});
	auto down = lock.add_command("spin-down", [&](i) {
		auto w = dials.writeable();
		--w[i];
	});
	auto open_lock = unlocked.add_command("open", []() {
		cout << "opening lock..." << endl;
	}).next_state(open);
	
	lock.initial({locked, unlocked});
	
	assert(lock.is_current(locked))
	assert(locked.is_current());
	
	open();		// <--- ignored
	close();	// <--- ignored
	
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











