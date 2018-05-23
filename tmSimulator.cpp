/*
*File name: tmSimulator.hpp
*Author: Daniele Huang
*Date:
*Description: this file contains the main method to run turing machines
*/

#include <stdio.h>
#include <fstream>
#include "TuringMachine.hpp"
#include "TuringMachineTransitions.hpp"

using namespace std;

int main ( int argc, char ** argv ){
   if( argc != 3 ){
      cout << "Invalid number of arguments. \n"
         << "Usage: ./tmSimulator <inputfile> <outputfile>\n";

         return -1;
   }
   TuringMachine * machine = new TuringMachine();

   if( !machine->loadFromFile( argv[1]) ){
      cout << "Error loading the input file!\n";
   }

   ofstream out;

   out.open( argv[2] );

   if ( !out.is_open() ){
      cout << "Error opening the output file!\n";
      return -1;
   }

   out.seekp( 0, ios_base :: beg);
   
   return 0;
}
