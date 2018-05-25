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
 static char getCharMove ( int move) {
   switch( move){
     case 0: return 'L';
     case 1: return 'S';
     case 2: return 'R';
   }
   return -1;
 }
 static int getArrayMove ( char move ){
   switch ( move){
     case 'L' : return -1;
     case 'S' : return 0;
     case 'R' : return 1;
   }
   return 0;
 }
 bool TuringMachine::loadFromFile( /*const char * in_filename */){

   cerr << "Start loading from input file"<< endl;
   //ifstream infile (in_filename);
   bool readState = 0;
   bool readAccept = 0;
   bool readMax = 0;
   bool readInputs = 0;
   bool readRun = 0;
   char  tr []= "tr";
   char max [] = "max";
   char acc [] = "acc";
   char run [] = "run";
  // string tr = new string (tri);
  /* string::size_type sz;

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
     }*/
  while(1){

     if(!cin) return true;
     vector<char* > entry;
     while( cin){

       string next;
       char * cpy = new char[10];
       cin >> next;
       strcpy  (cpy, next.c_str() );

       if( strcmp ( tr, cpy )== 0){

         //cerr<< "setting readState"<<endl;
         readState =1;
         continue;
       }
       else if (strcmp ( acc, cpy )== 0){
         //cerr<< "setting readAccept"<<endl;
         readAccept = 1;
         readState = 0;
         continue;
       }
       else if( strcmp (max, cpy )== 0){
         //cerr<< "setting readMax"<<endl;
         readAccept = 0;
         readMax = 1;
         continue;
       }
       else if( strcmp ( run , cpy )== 0){
         //cerr<< "setting readRun"<<endl;
         readMax = 0;
         readRun =1;
         continue;
       }



       if( readState){
         entry.push_back( cpy );
         if( entry.size() == 5 ) break;
       }
       else if( readAccept ){
         int accept  = stoi( cpy );
         acceptStates.push_back(accept);
        // cerr << "Inserting new accept state "<< accept << endl;
       }
       else if( readMax ){
         maxIterations = stoi(cpy);
         //cerr <<"Detecting new max "<< maxIterations << endl;
       }
       else if(  readRun ){
         inputs.push_back( cpy);
         //cerr << "Inserting new input: "<< cpy<< endl;
       }

     }
     //inserting new transitions
     if(readState){
       int sState = stoi(entry[0]);


       char * inputChar = entry[1];

       char * replace =entry[2];

       char * move = entry[3];

       int moveIndex = getIndex( *move);

       int nState = stoi( entry[4]);





        auto transIt = transitions->find(sState);

        //insert new starting state and all its associated input, replace, move, nextState
        if( transIt == transitions->end() ){
          map<char, map < char ,  vector <int>*   > > * inputMap =
                    new map<char, map < char, vector <int >*  > >;

          map < char,  vector <int>* > * replaceMap =
                    new map < char,  vector <int>* >;


          vector <int> movesVec  [3];
          vector<int> nStates;

          nStates.push_back(nState);
          movesVec[moveIndex] = nStates;

          replaceMap->insert( {replace[0], movesVec}   );

          inputMap->insert( {inputChar[0], *replaceMap} );
          transitions->insert( {sState, *inputMap});

        }
        //sState was already added to the hashmap
        else{
          map<char, map < char ,  vector <int>*   > >  inputMap =
               transIt->second;
               auto transInput = inputMap.find(*inputChar);
               //if inputChar has not been seen before
               if( transInput ==  inputMap.end() ){
                 //cerr<<"Inserting new input"<<endl;
                 map < char,  vector <int>* > * replaceMap =
                           new map < char,  vector <int>* >;


                 vector <int>  movesVec [3];
                 vector<int>  nStates ;

                 nStates.push_back(nState);
                 movesVec[moveIndex] = nStates;

                 replaceMap->insert( {replace[0], movesVec}   );

                 inputMap.insert( {inputChar[0], *replaceMap} );
               }
               //inputChar has already been seen
               else{
                   map < char,  vector <int>* >  replaceMap = transInput->second;
                   auto transReplace = replaceMap.find(*replace);
                   //if replace has not been seen before
                   if( transReplace == replaceMap.end()){
                      //cerr << "Inserting new replace"<<endl;
                      vector <int>  movesVec [3];
                      vector<int>  nStates ;

                      nStates.push_back(nState);
                      movesVec[moveIndex] = nStates;

                      replaceMap.insert( {replace[0], movesVec}   );
                   }
                   //replace has already been seen!
                   else{
                     vector <int> * movesVec = transReplace->second;
                     if( movesVec[moveIndex].size() == 0){
                       //cerr <<"inserting new move"<<endl;
                       vector<int> nStates;
                       nStates.push_back(nState);
                       movesVec[moveIndex ] = nStates;
                     }
                     else{
                       movesVec[moveIndex].push_back( nState);
                     }
                   }
               }
        }



     //TuringMachineTransitions * trans = new TuringMachineTransitions( sState, )
     //maybe store the transitions in a list of lists
     //where the big list is sorted by inputs ( use hashmap<char, vector<transitions> )
     //then each definition is a list of transitions sorted by the sState.

   }

}

   return true;
 }

 vector<char*> TuringMachine::getInputStrings(){
   return inputs;
 }


 int TuringMachine::getMaxLoops(){
   return maxIterations;
 }


 char TuringMachine::getReplace(int sState, char input){
   auto it = transitions->find(sState);
   if( it == transitions->end()) return '0';
   //valid startState
   else{

     auto inputMap = it->second;
     auto it0 = inputMap.find(input);
     if( it0 == inputMap.end()) return '0';
     //valid input
     else{
       auto it1 = inputMap.find( input);

       if( it1 == inputMap.end() ) return '0';
       else{
         return inputMap.begin()->first;
       }
     }
   }
 }
 char TuringMachine::getNextMove (int sState, char input, char replace){
   auto it = transitions->find(sState);
   auto inputMap = it->second;
   auto it1 = inputMap.find( input);
   auto replaceMap  = it1->second;
   auto it2 = replaceMap.find(replace);
   cerr <<"size"<<(it2->second)[0].size()<< endl;
   if( it2 == replaceMap.end() ) return  '0';
   else{
     for( int i=0; i < 3; i++){

       if( (it2->second)[i].size() !=0 ) return getCharMove(i);
     }
   }
   return '0';
 }
 int TuringMachine::getNState ( int sState, char input, char replace, char move){
   auto it = transitions->find(sState);
   auto inputMap = it->second;
   auto it1 = inputMap.find( input);
   auto replaceMap  = it1->second;
   auto it2 = replaceMap.find(replace);
   auto moves = it2->second;
   //next state vector
   auto it3 = moves[ getIndex(move) ];

   return it3[0];
 }

 int TuringMachine::computeNextState(int currIndex, int currState, char* input){
   int currentIndex = currIndex;
   int currentState = currState;
   cerr << "State | input "<<endl;
   cerr << currentState << "     " << input<<endl;
   for( int i =0 ; i < /*getMaxLoops()*/ 10; i ++){
     cerr << i<<endl;
     char currChar = input[currIndex];

     char replace =getReplace( currentState, currChar );   cerr << "Here! "<< replace <<endl;
     char move = getNextMove( currentState, currChar, replace);   cerr << "Yo! "<< move<<endl;
     int nState = getNState ( currentState, currChar, replace, move ); cerr  << "nst" << nState <<endl;
     //start operating
     input[currentIndex] = replace;
     currentIndex += getArrayMove( move);
     currentState = nState;
     cerr << currentState << "    " << input<<endl;
   }
   return 0;
 }
