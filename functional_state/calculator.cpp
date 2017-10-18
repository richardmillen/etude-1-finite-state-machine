////////////////////
// calculator.cpp //
////////////////////

// 
// https://en.wikipedia.org/wiki/UML_state_machine#Hierarchically_nested_states
// 

#include "fsm/context.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {
	context_t calc;

	unordered_map<string, ...> op_funcs = {
		{"+", plus()},
		{"-", minus()},
		{"/", divides()},
		{"*", multiplies()}
	}
	
	auto operand1 = 0.0f;
	auto operand2 = 0.0f;
	auto op_func = ...;
	
	state_t on("on");
	state_t op1("operand1");
	state_t op2("operand2");
	
	on.add_substate(op1);
	on.add_substate(op2);
	
	stream_t operand("operand", R"([\d\.])");
	stream_t oper("oper", R"([\+\-/\*])");
	stream_t equals("equals", "=");
	stream_t clear("clear", "[cC]");
	
	on.on_event(clear, [](ctx) {
		cout << "clearing..." << endl;
		ctx.reset();
	});
	
	op1.on_event(operand, [&](ctx) {
		operand1 = stof(ctx.stream().str());
		cout << operand1 << flush;
	});
	
	op1.on_event(oper, [](ctx) {
		cout << ctx.stream().str() << flush;
	}).next_state(op2);
	
	op2.on_event(operand, [&](ctx) {
		operand2 = stof(ctx.stream().str());
		cout << operand2 << flush;
	});
	
	op2.on_event(oper, [&](ctx) {
		op_func = op_funcs[ctx.stream().str()];
		ctx.stream().str("");
	}).next_state(op1);
	
	op2.on_event(equals, [](ctx) {
		auto total = op_func(operand1, operand2);
		ctx.next_stream() << total;
	}).next_state(op1)
	
	// all other connected states are implicitly added to calc:
	calc.initial_state(op1);
	
	calc.send("2");
	calc.send("+");
	calc.send("2");
	calc.send("*");
	calc.send("10");
	calc.send("=");
	calc.send("/");
	calc.send("2");
	
	return 0;
}








