/*
*File name: TuringMachineTransitions.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the state implementation for state machines
*/

#ifndef TuringMachineTransitions_HPP
#define TuringMachineTransitions_HPP

#include <string>
#include <iostream>
using namespace std;


//enum class Move { "R", "S", "L" };
class TuringMachineTransitions {

  private:
    int startState;
    char input;
    char replace;
    char move;
    int nextState;
  public:
    TuringMachineTransitions(int startState, char input, char replace, char move, int nextState);
    ~TuringMachineTransitions();

    int getStartState ();
    int getNextState () ;
    char getInput () ;
    char getReplace ();
    char getMove () ;




};

#endif
