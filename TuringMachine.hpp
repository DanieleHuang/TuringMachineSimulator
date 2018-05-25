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

    //vector<TuringMachineTransitions> transitions;     // vector containing all states
    //vector<char> inputString;             // vector containing an input string
    vector< char * > inputs;           //list containing all strings
    int maxIterations;
    vector<int> acceptStates; //the accept states
    vector<int> currentStates;   //the state we are on
    vector<int> currInputIndex;   //current char that we are processing

    vector<char *> currStrings;
  public:
    TuringMachine(void);                    //constr
    ~TuringMachine();
map< int , map< char , map < char, vector<int>*   > > > * transitions =
         new map< int , map< char , map < char, vector<int>*   > > >;

    bool loadFromFile( /*const char * in_filename */);

    //compute next state according to input character
    int computeNextState(int currIndex, int currState, char* input);
    int getMaxLoops();

    char getReplace(int sState, char input);
    char getNextMove (int sState, char input, char replace);
    int getNState ( int sState, char input, char replace, char move);
    vector <char *>  getInputStrings();

};

#endif
