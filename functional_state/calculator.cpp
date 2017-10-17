////////////////////
// calculator.cpp //
////////////////////

// 
// https://en.wikipedia.org/wiki/UML_state_machine#Hierarchically_nested_states
// 

#include "fsm/context.hpp"

int main(int argc, char* argv[]) {
	context_t calc;
	
	auto on = calc.add_state("on");
	auto op1 = on.add_substate("operand1");
	auto op2 = on.add_substate("operand2");
	auto op = on.add_substate("opEntered");
	auto result = on.add_substate("result");
	
	
	
	
	
	return 0;
}








