#include "turnstile1.hpp"

#include "fsm/context.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	context turnstile;

	configure(turnstile);
	
	vector<string> inputs = { "push", "pull!", "coin", "push", "token", "push", "push", 
							  "coin", "coin", "push", "kick!", "coin", "push" };
	
	for (auto& in : inputs)
		cout << in << ":" << turnstile.input(in);
	
	return 0;
}
