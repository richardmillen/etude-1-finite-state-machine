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

using namespace std;

int main(int argc, char* argv[]) {
	context_t calc;
	
	auto op1_stream = calc.add_stream("operand1", R"([\d\.])");
	auto op2_stream = calc.add_stream("operand2", R"([\d\.])");
	auto oper_stream = calc.add_stream("opEntered", R"([\+\-/\*])");
	auto res_stream = calc.add_stream("result", "=");
	auto clear = calc.add_command("clear");
	
	auto op1_value = 0.0f;
	auto op2_value = 0.0f;
	
	auto on = calc.add_state("on")
		(clear, [](ctx) {
			cout << "clearing..." << endl;
			ctx.reset();
		});
	
	auto oper = on.add_substate("opEntered")
		(oper_stream, [](ctx) {
			cout << ctx.input() << endl;
		});
	
	auto op1 = oper.add_substate("operand1");
		(op1_stream, [](ctx) {
			op1_value = stof(ctx.stream().str());
			cout << op1_value << flush;
		});
	
	auto op2 = oper.add_substate("operand2");
		(op2_stream, [](ctx) {
			op2_value = stof(ctx.stream().str());
			cout << op2_value << flush;
		});
	
	auto result = op2.add_next_state("result");
		(res_stream, [](ctx) {
			auto op = ctx.conditions[ctx.streams["opEntered"].str()];
			auto total = op(op1_value, op2_value);
			ctx.push(total);
		}).next(op1);
	
	result.add_conditions({
		{"+", plus()},
		{"-", minus()},
		{"/", divides()},
		{"*", multiplies()}
	});
	
	calc.initial_state(op1);
	
	calc.execute("2");
	calc.execute("+");
	calc.execute("2");
	
	return 0;
}








