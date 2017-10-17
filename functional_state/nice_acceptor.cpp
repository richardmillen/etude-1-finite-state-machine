/////////////////////
// "nice" acceptor //
/////////////////////

#include "fsm/context.hpp"

#include <iostream>
#include <string>
#include <functional>

using namespace std;

int main(int argc, char* argv[]() {
	context_t acceptor;
	
	auto input = acceptor.add_stream("input");
	
	auto invalid = acceptor.add_default_state("not accepting").stream(input);
	auto ok = acceptor.add_state("accepting").stream(input, "nice");
	auto done = ok.add_next("done");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == invalid);
	assert(acceptor.current_state() == "not accepting");

	acceptor.recv("n");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == ok);
	assert(acceptor.current_state() == "accepting");

	acceptor.recv("i");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == ok);
	assert(acceptor.current_state() == "accepting");

	acceptor.recv("c");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == ok);
	assert(acceptor.current_state() == "accepting");

	acceptor.recv("e");
	
	assert(input.str() == "nice");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == done);
	assert(acceptor.current_state() == "done");
	
	acceptor.recv("!");
	
	assert(input.str() == "nice");
	
	cout << "input (unchanged): " << input.str() << endl;
	assert(acceptor.current_state() == done);
	assert(acceptor.current_state() == "done");

	cout << "let's start over!" << endl;
	
	acceptor.reset();
	
	assert(input.str() == "");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == invalid);
	assert(acceptor.current_state() == "not accepting");
	
	acceptor.recv("ni");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == ok);
	assert(acceptor.current_state() == "accepting");
	
	acceptor.recv("ny muggins");
	
	cout << "input: " << input.str() << endl;
	assert(acceptor.current_state() == invalid);
	assert(acceptor.current_state() == "not accepting");
	
	return 0;
}
















