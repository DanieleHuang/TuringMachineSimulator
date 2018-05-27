/*
*File name: tmSimulator.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the main method to run turing machines
*/

#include <stdio.h>
#include <fstream>
#include "TuringMachine.hpp"
#include "TuringMachineTransition.hpp"

using namespace std;

int main ( int argc, char ** argv ){
   if( argc != 3 ){
      cout << "Invalid number of arguments. \n"
         << "Usage: ./tmSimulator < <inputfile> <outputfile> <d/n>\n";

         return -1;
   }
   if( *argv[2] != 'd'  && *argv[2] != 'w'){
     cout << "Invalid flag." << endl;
     return -1;
   }
   bool deterministic =false;
   if( *argv[2] == 'd') deterministic = true;
   TuringMachine * machine = new TuringMachine();

   if( !machine->loadFromFile(/* argv[1])*/ )){
      cout << "Error loading the input file!\n";
      return -1;
   }

   ofstream out;

   out.open( argv[1] );

   if ( !out.is_open() ){
      cout << "Error opening the output file!\n";
      return -1;
   }

   out.seekp( 0, ios_base :: beg);

   auto it = machine->transitions->begin();
   for( it; it != machine->transitions->end(); it++){

     auto input = it->second;
     auto it0 = input.begin();
     for( it0; it0 != input.end(); it0++ ){
       for( int i =0; i<(it0->second).size(); i++)
       cout << it->first << it0-> first <<(it0->second)[i]<< " ";
     }
   }
   cout << endl;

   vector<char*> inputStrings = machine->getInputStrings();
   char* first = inputStrings[0];

   bool result = 0;
   if( deterministic)
     result = machine->computeNextState(0,0, first );
   if( !result) return -1;
   return 0;
}
