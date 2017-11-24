/////////////////////
// "nice" acceptor //
/////////////////////

#include "fsm/context.hpp"

#include <iostream>
#include <string>
#include <functional>

using namespace std;

int main(int argc, char* argv[]() {
	context acceptor;
	
	stream any_in("input");
	stream nice_in("nice", "nice");
	
	state invalid("not accepting");
	state ok("accepting");
	
	invalid.add_substate(ok);
	
	invalid.on_event(any_in, [](ctx) {
		cout << "invalid input: " << ctx.string() << endl;
	});
	invalid.on_event(nice_in, [](ctx) {
		cout << "input: " << ctx.string() << endl;
	}).next_state(ok);
	
	acceptor.initial_state(invalid);
	
	acceptor.send("n");
	assert(acceptor.current_state() == invalid);

	acceptor.send("i");
	assert(acceptor.current_state() == invalid);

	acceptor.send("c");
	assert(acceptor.current_state() == invalid);

	acceptor.send("e");
	assert(acceptor.current_state() == ok);
	
	acceptor.send("!");
	assert(acceptor.current_state() == invalid);	
	
	cout << "let's start over!" << endl;
	
	acceptor.reset();
	
	assert(acceptor.current_state() == invalid);
	assert(acceptor.current_state() == "not accepting");
	
	acceptor.send("ni");
	assert(acceptor.current_state() == invalid);
	
	acceptor.send("ce");
	assert(acceptor.current_state() == ok);
	
	return 0;
}
















