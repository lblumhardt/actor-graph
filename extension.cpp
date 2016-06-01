#include "ActorGraph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char *argv[]) {

  //check number of args
  if(argc != 4) {
    cout << "ERROR! Incorrect number of command line arguments \n";
    return -1;
  }

  //process the first arg
  const char* file = argv[1]; 

  //process the second arg
  //you should do a check on argv[2] tho
  std::filebuf f;
  f.open(argv[2], std::ios::in); 
  std::istream actor(&f);
  
  //process the third arg
  std::ofstream output(argv[3], std::ofstream::out);
  output << "Actor	Avg Distance\n";
  
  
  ActorGraph graph;
  graph.loadFromFile(file, true); 

  graph.buildGraph();
  bool have_header = false;
  vector<tuple<string,string,int>> pathsToFind;
 
  while(actor) {

    string tmp;
    if(!getline(actor, tmp)) {
      break;
    }

    if(!have_header) {
      have_header = true;
      continue;
    }
 
    istringstream ss(tmp);
    vector<string> toFind;
    while(ss) {
      string next;

      if(!getline(ss, next, '\n')) {
        break;
      }
      toFind.push_back(next);
      vector<pair<string,Movie*>> outPath;
      if(toFind.size() == 1) {
        cout << "it worked! I found: " << toFind[0] << "\n"; 
        double avg = graph.findAverage(toFind[0]);
        cout << "and his avg was: " << avg << "\n";
        toFind.clear();
      }
    }
  } 
  return 1;
  f.close();
  output.close();
}
 

