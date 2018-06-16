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
    int acceptState; //the accept state
    vector<int> currentStates;   //the state we are on
    vector<int> currInputIndex;   //current char that we are processing

    vector<char *> currStrings;   //all strings of a computation
  public:
    TuringMachine(void);                    //constr
    ~TuringMachine();
    map< int , map< char , vector<char*>  > > * transitions;
    bool loadFromFile( /*const char * in_filename */);

    //compute next state according to input character
    char* computeNextState(int *currIndex,int *currState, char* input);
    //run the string on the given turing machine
    bool compute( char* input);
    int getMaxLoops();

    //get replace, remove, and nextState, returns a char pointer in the format
    //RMN, where R is the replacing letter, M is the move, and N is the next state
    char* getRepMoveNext(int sState, char input);

    //determines if the machine has run into the accept state
    bool isAcceptState(int state);
    vector <char *>  getInputStrings();

};

#endif
