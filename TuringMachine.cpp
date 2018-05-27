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

 TuringMachine::TuringMachine(void){
   cerr <<"Creating a new Turing Machine!"<<endl;
   transitions = new map< int , map< char , vector<char*>  > >;
 }
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

 static char getReplace ( char* rmn ){
   return rmn[0];
 }

 static char getMove ( char* rmn ){
   return rmn[1];
 }

 //can only handle single digit state
 static int getNext ( char* rmn ){
   return (rmn[2]- '0');
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

       char * next = entry[4];
       int moveIndex = getIndex( *move);

       int nState = stoi( entry[4]);

       char rmn0 [3];

       //build string with replace, move and next
       strcpy ( rmn0, replace);
       strcat ( rmn0, move);
       strcat ( rmn0, next);

       char * rmn = new char[3];
       strncpy( rmn, rmn0, 3);



        auto transIt = transitions->find(sState);

        //insert new starting state and all its associated input, replace, move, nextState
        if( transIt == transitions->end() ){
          map<char, vector<char*>    > * inputMap = new map<char, vector<char*> >;

          vector < char* > *  replaceMap = new vector<char*>;


          replaceMap->push_back( rmn);

          inputMap->insert( {inputChar[0], *replaceMap} );
          transitions->insert( {sState, *inputMap});
          cerr<< "new sState " <<sState << " " <<inputChar << " " <<replace << " " << move << " " << next <<endl;
         }
        //sState was already added to the hashmap
        else{
           map<char, vector<char*> >   inputMap = transIt->second;
           auto transInput = inputMap.find(*inputChar);

           //if inputChar has not been seen before
           if( transInput ==  inputMap.end() ){
                  //cerr<<"Inserting new input"<<endl;
              auto replaceVector = new vector<char*>;

              replaceVector->push_back(rmn);


              inputMap.insert( {inputChar[0], *replaceVector} );
              cerr<< "new Input "<<sState << " " <<inputChar << " " <<replace << " " << move << " " << next <<endl;

              cerr << "Size of Map " << transIt->first << " is "<< (transIt->second).size()<<endl;
              transInput = inputMap.begin();
              for(transInput; transInput!= inputMap.end(); transInput++ )
                cout << transInput->first <<(transInput->second)[0]<< " ";
              cout << endl;
            }

            //inputChar has already been seen
            else{
              auto replaceMap = transInput-> second;
              replaceMap.push_back(rmn);
              cerr<< "new replace " <<sState << " " <<inputChar << " " <<replace << " " << move << " " << next <<endl;

            }
          }
        }
        cerr << "@@@@@ Map contains : "<<endl;
        auto it = transitions->begin();
        for( it; it != transitions->end(); it++){
          cout <<  it->first << " size: " << it->second.size() <<endl;
          auto input = it->second;
          auto it0 = input.begin();
          for( it0; it0 != input.end(); it0++ ){
            cout <<  "\t( \"" <<it0->first<< "\" size: "<< (it0->second).size() << " )"<<endl;
            //for( int i = 0; i < (it0->second).size(); i++)
              cout << it->first << it0->first << (it0->second)[0]<< " ";
          }
          cout<< endl;
        }
        cerr << "$$$$$$$$$$$$"<<endl<<endl;



     //TuringMachineTransitions * trans = new TuringMachineTransitions( sState, )
     //maybe store the transitions in a list of lists
     //where the big list is sorted by inputs ( use hashmap<char, vector<transitions> )
     //then each definition is a list of transitions sorted by the sState.

   }



   return true;
 }

 vector<char*> TuringMachine::getInputStrings(){
   return inputs;
 }


 int TuringMachine::getMaxLoops(){
   return maxIterations;
 }


 char* TuringMachine::getRepMoveNext(int sState, char input){
   auto it = transitions->find(sState);
   //sState not found
   if( it == transitions->end()) return NULL;
   //sState found
   else{
     auto inputMap = it->second;
     auto it0 = inputMap.find( input);
     if( it0 == inputMap.end() ) return NULL;
     else{
       char * rmn = (it0->second)[0];
       return rmn;
     }
   }
   return NULL;
 }


  bool TuringMachine::computeNextState(int currIndex, int currState, char* input){
   int currentIndex = currIndex;
   int currentState = currState;
   cerr << "State | input "<<endl;
   cerr << currentState << "     " << input<<endl;
   for( int i =0 ; i < /*getMaxLoops()*/ 10; i ++){
     char currChar = input[currIndex];
     char* rmn =  getRepMoveNext( currentState, currChar);
     if ( !rmn){
       cout << "Something went wrong!\n";
       return false;
     }
     char replace = getReplace( rmn);
     char move = getMove(rmn);
     int nState  = getNext(rmn);
     cerr << "Applying: "<< currentState << " "<< currChar << " " <<
              replace << " "<< move << " "<<nState <<endl;

     //start operating
     input[currentIndex] = replace;
     currentIndex += getArrayMove( move);
     currentState = nState;
     cerr << currentState << "    " << input<<endl;
   }
   return true;
 }
