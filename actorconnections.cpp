//* Lucas Blumhardt A12020745 */
#include <fstream>
#include <sstream>
#include <iostream>
#include <tuple>
#include "ActorGraph.hpp"

std::string formString(tuple<string,string,int> t) {
  string retString;
  retString = get<0>(t) + "\t" + get<1>(t) + "\t" + to_string(get<2>(t)) + "\n";
  return retString;
}

int main(int argc, char *argv[]) {

  //check number of args
  if(argc != 5) {
    cout << "ERROR! Incorrect number of command line arguments \n";
    return -1;
  }

  //process the first arg
  const char* file = argv[1]; 

  //process the second arg
  //you should do a check on argv[2] tho
  std::filebuf f;
  f.open(argv[2], std::ios::in); 
  std::istream actorPairs(&f);
  
  //process the third arg
  std::ofstream output(argv[3], std::ofstream::out);
  output << "Actor1	Actor2	Year\n";
  
  //process the fourth arg
  string fourthArg = argv[4];
  bool bfs = true;
  if(fourthArg == "bfs") {
    bfs = true;
  }
  else if(fourthArg == "ufind") {
    bfs = false;
  }
  else {
    cout << "ERROR! Fourth argument should be either bfs or ufind \n";
    return -1;
  }

  ActorGraph* graph = new ActorGraph();
  graph->loadFromFile(file, true); 
  //graph.buildGraph();
  bool have_header = false;
  vector<tuple<string,string,int>> pathsToFind;
 
  while(actorPairs) {

    string tmp;
    if(!getline(actorPairs, tmp)) {
      break;
    }

    if(!have_header) {
      have_header = true;
      continue;
    }
 
    istringstream ss(tmp);
    vector<string> apair;
    while(ss) {
      string next;

      if(!getline(ss, next, '\t')) {
        break;
      }
      apair.push_back(next);
      vector<pair<string,Movie*>> outPath;
      if(apair.size() == 2) {
        pathsToFind.push_back(make_tuple(apair[0],apair[1],9999));
        //cout << "Currently finding a path between " << apair[0] << " and " << apair[1] << "\n";
        apair.clear();
      }
    }
  } 
  if(bfs) {
    graph->buildBFS(pathsToFind);
  }
  else {
    graph->buildUFIND(pathsToFind);    
  }
  for(tuple<string,string,int> &tup : pathsToFind) {
    output << formString(tup);
  } 

  delete graph;

  //dummy return value
  output.close();
  f.close();
  return 1;
}
