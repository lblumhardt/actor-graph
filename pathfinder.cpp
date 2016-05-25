/* Lucas Blumhardt A12020745 */
#include <fstream>
#include <sstream>
#include <iostream>
#include "ActorGraph.hpp"

int main(int argc, char *argv[]) {

  //check number of args
/*  if(argc != 5) {
    cout << "ERROR! Incorrect number of command line arguments \n";
    return -1;
  }
*/
  //process the first arg
  const char* file = argv[1]; 

  //process the second arg (u or w)
  char* temp = argv[2];
  bool weighted = true;
  if(*temp == 'u') {
    weighted = false;
  } 
  else if(*temp == 'w') {
    weighted = true;
  }
/*  else {
    cout << "ERROR! Second argument should be either 'w' or 'u' \n";
    return -1;
  }
*/
  //process the third arg
  //you should do a check on argv[3] tho
  std::filebuf f;
  f.open(argv[3], std::ios::in); 
  std::istream actorPairs(&f);
  
  //process the fourth arg
  std::ofstream output(argv[4], std::ofstream::out);

  ActorGraph graph;
  graph.loadFromFile(file, weighted); 

  //distance is 1, should work
  //graph.findPath("ROCK LEE", "MIGHT GUY");
  graph.findPath("ROCK LEE", "JAMES PERSON");

/* 
  //invalid actors, should fail
  graph.findPath("rock Lee", "MIGHT GUY");
  graph.findPath("ROCK LEE", "MIGHT DIE");

  //not in the same movie, should fail
  graph.findPath("ROCK LEE", "JAMES PERSON");
*/
  //dummy return value
  output.close();
  f.close();
  return 1;
} 
