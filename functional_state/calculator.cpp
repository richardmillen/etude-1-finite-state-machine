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
	
	auto operand = calc.add_stream("operand", R"([\d\.])");
	auto oper = calc.add_stream("oper", R"([\+\-/\*])");
	auto result = calc.add_stream("result", "=");
	auto clear = calc.add_command("clear");

	unordered_map<string, ...> op_funcs = {
		{"+", plus()},
		{"-", minus()},
		{"/", divides()},
		{"*", multiplies()}
	}
	
	auto operand1 = 0.0f;
	auto operand2 = 0.0f;
	auto op_func = ...;
	
	auto on = calc.add_state("on")
		(clear, [](ctx) {
			cout << "clearing..." << endl;
			ctx.reset();
		});
	
	on.add_substate("operand1")
		(operand, [&](ctx) {
			operand1 = stof(ctx.stream().str());
			cout << operand1 << flush;
		})
		(oper, [](ctx) {
			cout << ctx.stream().str() << flush;
		}).add_next("operand2")
			(operand, [&](ctx) {
				operand2 = stof(ctx.stream().str());
				cout << operand2 << flush;
			})
			(oper, [&](ctx) {
				op_func = op_funcs[ctx.stream().str()];
			}).next_state("operand1")
			(result, [](ctx) {
				auto total = op_func(operand1, operand2);
				ctx.send_next(total);
			}).next_state("operand1")
			;
	
	calc.initial_state(op1);
	
	calc.execute("2");
	calc.execute("+");
	calc.execute("2");
	calc.execute("*");
	calc.execute("10");
	calc.execute("=");
	calc.execute("/");
	calc.execute("2");
	
	return 0;
}








