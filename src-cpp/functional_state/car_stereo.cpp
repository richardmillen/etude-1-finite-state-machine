#include "fsm/context.hpp"

#include <iostream>
#include <string>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    	context stereo;
	
	stream cmd_back("back", "<");
	stream cmd_next("next", ">");
	stream cmd_cd("cd", "cd");
	stream cmd_radio("radio", "radio");
	stream cmd_on("on", "on");
	stream cmd_off("off", "off");
	
	condition start_mode([](s) {
		return "cd" == s.name();
	});
	
	state off("off");
	state on("on");
	state cd("cd");
	state radio("radio");
	
	on.add_substate(cd);
	on.add_substate(radio);
	
	cd.add_condition(mode);
	radio.add_condition(mode);
	
	off.on_event(cmd_on, [](ctx) {
		cout << "off: turning on..." << endl;
	}).next_state(start_mode, {cd, radio});
	
	on.on_enter([](ctx) {
		cout << "on: entering state..." << endl;
	});
	on.on_event(cmd_off, [](ctx) {
		cout << "on: turning off..." << endl;
	}).next_state(off);
	on.on_exit([](ctx) {
		cout << "on: leaving state..." << endl;
	});
	
	cd.on_event(cmd_back, [](ctx) {
		cout << "cd: back" << endl;
	});
	cd.on_event(cmd_next, [](ctx) {
		cout << "cd: next" << endl;
	});
	cd.on_event(cmd_radio, [](ctx) {
		cout << "cd: switching to radio..." << endl;
	}).next_state(radio);
    	
	radio.on_event(cmd_back, [](ctx) {
		cout << "radio: back" << endl;
	});
	radio.on_event(cmd_next, [](ctx) {
		cout << "radio: next" << endl;
	});
	radio.on_event(cmd_cd, [](ctx) {
		cout << "radio: switching to cd player..." << endl;
	}).next_state(cd);
	
    	stereo.send("off");      	// <--- ignored
    	stereo.send("hello");    	// <--- ignored
   	 
    	stereo.send("on");
    	stereo.send(">");
    	stereo.send(">");
    	stereo.send("<");
    	stereo.send("radio");
    	stereo.send(">");
    	stereo.send("<");
    	stereo.send("off");
	
    	stereo.send(">");     		// <--- ignored

    	return 0;
}



