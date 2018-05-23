/*
*File name: TuringMachineTransitions.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the state implementation for state machines
*/


#include <string>
#include <iostream>
#include "TuringMachineTransitions.hpp"
using namespace std;

TuringMachineTransitions::TuringMachineTransitions(int sState, char in,
                                       char rep, Move mv, int nState){

   startState = sState;
   input = in;
   replace = rep;
   move = mv;
   nextState = nState;
}

TuringMachineTransitions::~TuringMachineTransitions(){}

int TuringMachineTransitions::getStartState () { return startState; }

int TuringMachineTransitions::getNextState () { return nextState; }

char TuringMachineTransitions::getInput () {return input; }

char TuringMachineTransitions::getReplace () { return replace; }

Move TuringMachineTransitions:: getMove () { return move; }
