#include "fsm/context.hpp"

#include <iostream>
#include <string>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    	context_t stereo;
	
    	auto back = stereo.add_command(equal_to("back"));
    	auto next = stereo.add_command(equal_to("next"));
    	auto cd = stereo.add_command(equal_to("cd"));
    	auto radio = stereo.add_command(equal_to("radio"));
    	auto on = stereo.add_command(equal_to("on"));
    	auto off = stereo.add_command(equal_to("off"));
	
    	stereo.add_initial("off")
        	(on, [](ctx) {
            		cout << "turning on..." << endl;
        	}).on_exit([](ctx) {
            		ctx.next_state(ctx.conditions["default"]);
        	})
        	;
    	
    	stereo.add_state("cd")
        	(back, [](ctx) {
            		cout << "cd: back" << endl;
        	})
        	(next, [](ctx) {
            		cout << "cd: next" << endl;
        	})
        	(off, [](ctx) {
            		cout << "cd: off" << endl;
        	}).add_next("off")
        	(radio, [](ctx) {
            		cout << "cd: switching to radio..." << endl;
        	}).add_next("radio")
            		(back, [](ctx) {
                		cout << "radio: back" << endl;
            		})
            		(next, [](ctx) {
                		cout << "radio: next" << endl;
            		})
            		(off, [](ctx) {
                		cout << "radio: off" << endl;
            		}).add_next("off")
            		(cd, [](ctx) {
                		cout << "radio: switching to cd player..." << endl;
            		}).add_next("cd");
            		;
   	 
    	stereo.conditions["default"] = "cd";
		
    	stereo.execute("off");      // <--- ignored
    	stereo.execute("hello");    // <--- ignored
   	 
    	stereo.execute("on");
    	stereo.execute("next");
    	stereo.execute("next");
    	stereo.execute("back");
    	stereo.execute("radio");
    	stereo.execute("next");
    	stereo.execute("back");
    	stereo.execute("off");
	
    	stereo.execute("next");     // <--- ignored

    	return 0;
}



