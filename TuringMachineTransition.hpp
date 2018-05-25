/*
*File name: TuringMachineTransitions.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the state implementation for state machines
*/

#ifndef TuringMachineTransition_HPP
#define TuringMachineTransition_HPP

#include <string>
#include <iostream>
using namespace std;


//enum class Move { "R", "S", "L" };
class TuringMachineTransition {

  private:
    int startState;
    char input;
    char replace;
    char move;
    int nextState;
  public:
    TuringMachineTransition(int startState, char input, char replace, char move, int nextState);
    ~TuringMachineTransition();

    int getStartState ();
    int getNextState () ;
    char getInput () ;
    char getReplace ();
    char getMove () ;




};

#endif
