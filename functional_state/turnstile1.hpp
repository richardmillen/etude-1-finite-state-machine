#pragma once

#include "fsm/context.hpp"

#include <iostream>
#include <string>

void assemble(context_t& turnstile) {
    auto locked = turnstile.add_state("locked");
	auto unlocked = turnstile.add_state("unlocked");
	
	locked.on_event([](ctx) {
		return (ctx.input() == "coin");
	}).transition([](ctx) {
		std::cout << "your " << ctx.input() << " was accepted, thanks!" << std::endl;
	}).next(unlocked);
	
	locked.on_event([](ctx) {
		return (ctx.input() == "token");
	}).transition(locked.transitions().front());
	
	locked.on_enter([](ctx) {
		std::cout << "entering locked state..." << std::endl;
	});
	locked.on_exit([](ctx) {
		std::cout << "leaving locked state..." << std::endl;
	});
	
	locked.on_error([](ctx) {
		if (ctx.input() == "push") {
			std::cout << "you have to pay first buddy!" << std::endl;
			ctx.handled = true;
		}
	});
	
	unlocked.on_event([](ctx) {
		return (ctx.input() == "push");
	}).transition([](ctx) {
		std::cout << "turning..." << std::endl;
	}).next(locked);
	
	unlocked.on_enter([](ctx) {
		std::cout << "entering unlocked state..." << std::endl;
	});
	unlocked.on_exit([](ctx) {
		std::cout << "leaving unlocked state..." << std::endl;
	});
	
	unlocked.on_error([](ctx) {
		if (ctx.input() == "coin") {
			std::cout << "you've already paid!" << std::endl;
			ctx.handled = true;
		}
	});

	turnstile.on_error([](ctx) {
		std::cout << "je ne comprends pas!" << std::endl;
		ctx.handled = true;
	}
	
	turnstile.initial(locked);
}
