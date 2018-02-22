// https://en.wikipedia.org/wiki/State_pattern

#include "context.hpp"
#include "state.hpp"

int main(int argc, char* argv[]) {
	context_t context;
	
	context.write("Monday");
	context.write("Tuesday");
	context.write("Wednesday");
	context.write("Thursday");
	context.write("Friday");
	context.write("Saturday");
	context.write("Sunday");
	
	return 0;
}


