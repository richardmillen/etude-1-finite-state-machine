# Functional State

This folder contains a number of examples / use cases for a finite-state machine, with a functional (rather than imperitive) flavour.

For instance all input events are handled by lambda functions, regular expressions are used to determine if/when/how input should be handled and conditions may be defined against a state that determine whether it may be entered. 

## The Examples

The example source files in this directory are currently *rough sketches* and therefore won't compile. 

I used them as a way of exploring potential design requirements of a simple finite-state machine api.

## The FSM

The 'fsm' directory contains a *first stab* at an implementation, along with a basic test suite.

Not all features required by the examples have been implemented, most notably the 'state timer'. I left the timer for now as it's not an important feature.

I expect many of the examples will become working implementations in the future.



