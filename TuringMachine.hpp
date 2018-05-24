/*
*File name: TuringMachine.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the data structures to support the mechanics
*for Turing Machines.
*/

#ifndef TURINGMACHINE_HPP
#define TURINGMACHINE_HPP

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include "TuringMachineTransition.hpp"

using namespace std;

class TuringMachine {
  private:
    map< int , map< char , map < char, vector<int>*   > > > transitions;
    //vector<TuringMachineTransitions> transitions;     // vector containing all states
    //vector<char> inputString;             // vector containing an input string
    vector<vector<char>> inputs;           //list containing all strings
  public:
    TuringMachine(void);                    //constr
    ~TuringMachine();

    int maxIterations;
    int acceptState;

    bool loadFromFile( const char * in_filename );

    //compute next state according to input character
    int computeNextState(char input, int indexOfInput, vector<char> * inputString,
      TuringMachineTransitions state  );
};

#endif
