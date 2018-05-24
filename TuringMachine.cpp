/*
 * TuringMachine.cpp
 * Daniele Huang
 * This file contains the implementation of the Turing Machine class
 */

 #include <fstream>
 #include <sstream>
 #include <string.h>
 #include <stdio.h>
 #include "TuringMachine.hpp"
 #include "TuringMachineTransition.hpp"

 using namespace std;

 TuringMachine::TuringMachine(void){ cerr <<"Creating a new Turing Machine!"<<endl; }
 TuringMachine::~TuringMachine(){ }

 static int getIndex ( char move ){
   switch( move ) {
      case 'L' : return 0;
      case 'S' : return 1;
      case 'R' : return 2;
   }
   return -1;
 }
 bool TuringMachine::loadFromFile( const char * in_filename){

   cerr << "Start loading from input file"<< endl;
   ifstream infile (in_filename);
   int readState = 1;
   int readAccept = 0;
   int readMax = 0;
   int readInputs = 0;
   char  tr []= "tr";
  // string tr = new string (tri);
   string::size_type sz;

   cerr << "Start Parsing"<<endl;
   while(infile){
     string s;
     if( !getline ( infile, s)) break;

     istringstream ss(s);

     vector<string> entry;
     while(ss && readState) {
       string next;
       char * cpy = new char[10];

       if(!getline( ss, next, ' ' ) )break;  //need to understand what ss is for
       strcpy( cpy, next.c_str());

       if(strcmp(tr, cpy)!= 0){
          entry.push_back( next );
        }


       if( entry.size() == 5 ) break;
     }


     int sState = 0;
     if ( ! (istringstream(entry[0]) >> sState) ) sState = 0;

     char * inputChar = new char[1];
     strcpy( inputChar, entry[1].c_str());
     char * replace = new char [1];
     strcpy( replace, entry[2].c_str());
     char * move = new char[1];
     strcpy( move, entry[3].c_str());
     int moveIndex = getIndex( move[0]);

     int nState = 0;
     if ( ! (istringstream(entry[4]) >> nState) ) nState = 0;

     cout << "Inserting: "<< sState << " " << inputChar[0] << " " << replace[0]
              << " " << move[0] << " " << nState<< endl;

     auto transIt = transitions.find(sState);

     //insert new starting state and all its associated input, replace, move, nextState
     if( transIt == transitions.end() ){
        cerr <<"Inside!"<<endl;
        map<char, map < char ,  vector <int>*   > > * inputMap =
                    new map<char, map < char, vector <int >*  > >;

        map < char,  vector <int>* > * replaceMap =
                    new map < char,  vector <int>* >;


        vector <int> * movesVec  = new vector<int>[3];
        vector<int> * nStates = new vector <int>;

        nStates->push_back(nState);
        movesVec[moveIndex] = *nStates;

        replaceMap->insert( {replace[0], movesVec}   );

        inputMap->insert( {inputChar[0], *replaceMap} );


     }
     //TuringMachineTransitions * trans = new TuringMachineTransitions( sState, )
     //maybe store the transitions in a list of lists
     //where the big list is sorted by inputs ( use hashmap<char, vector<transitions> )
     //then each definition is a list of transitions sorted by the sState.

   }


   return true;
 }
