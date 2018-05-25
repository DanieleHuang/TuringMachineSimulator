/*
*File name: TuringMachineTransitions.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the state implementation for state machines
*/


#include <string>
#include <iostream>
#include "TuringMachineTransition.hpp"
using namespace std;

TuringMachineTransition::TuringMachineTransition(int sState, char in,
                                       char rep, char mv, int nState){

   startState = sState;
   input = in;
   replace = rep;
   move = mv;
   nextState = nState;
}

TuringMachineTransition::~TuringMachineTransition(){}

int TuringMachineTransition::getStartState () { return startState; }

int TuringMachineTransition::getNextState () { return nextState; }

char TuringMachineTransition::getInput () {return input; }

char TuringMachineTransition::getReplace () { return replace; }

char TuringMachineTransition:: getMove () { return move; }
