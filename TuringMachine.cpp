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
 #include "TuringMachineTransitions.hpp"

 using namespace std;

 TuringMachine::TuringMachine(void){ }
 TuringMachine::~TuringMachine(){ }

 bool TuringMachine::loadFromFile( const char * in_filename){
   ifstream infile (in_filename);
   int readState = 1;
   int readAccept = 0;
   int readMax = 0;
   int readInputs = 0;
   char tr[] = "tr";
   while(infile){
     string s;
     if( !getline ( infile, s)) break;

     istringstream ss(s);
     vector<string> entry;
     while(ss && readState){
       string next;
       if(!getline( ss, next, ' ' ) )break;
       if(memcmp(&next,tr,2))continue;


       entry.push_back( next );
     }

     int sState = stoi( entry[0]);
     char * inputChar = new char[1];
     memcpy( inputChar, &entry[1],1);
     char * replace = new char [1];
     memcpy( replace, &entry[2],1);
     int nState = stoi( entry[3]);

     //TuringMachineTransitions * trans = new TuringMachineTransitions( sState, )
     //maybe store the transitions in a list of lists
     //where the big list is sorted by inputs ( use hashmap<char, vector<transitions> )
     //then each definition is a list of transitions sorted by the sState.

   }


   return true;
 }
