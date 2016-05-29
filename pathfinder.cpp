/* Lucas Blumhardt A12020745 */
#include <fstream>
#include <sstream>
#include <iostream>
#include "ActorGraph.hpp"

std::string formOutputString(vector<std::pair<std::string, Movie*>> v) {
  //if v's size is 0, the find failed, don't add anything
  string a;
  Movie* m;
  string retString;
  for(int i=0; i < v.size(); i++) {
    auto p = v[i];
    a = p.first;
    m = p.second;
    retString = retString + "(" + a + ")";
    if(m != nullptr) {
      retString = retString + "--[" + m->getTitle() + "#@" + to_string(m->getYear()) + "]-->";
    }
  }
  retString = retString + "\n";
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

  //process the second arg (u or w)
  char* temp = argv[2];
  bool weighted = true;
  if(*temp == 'u') {
    weighted = false;
  } 
  else if(*temp == 'w') {
    weighted = true;
  }
  else {
    cout << "ERROR! Second argument should be either 'w' or 'u' \n";
    return -1;
  }

  //process the third arg
  //you should do a check on argv[3] tho
  std::filebuf f;
  f.open(argv[3], std::ios::in); 
  std::istream actorPairs(&f);
  
  //process the fourth arg
  std::ofstream output(argv[4], std::ofstream::out);
  output << "(actor)--[movie#@year]-->(actor)--...\n";
  ActorGraph graph;
  graph.loadFromFile(file, weighted); 
  graph.buildGraph();
  bool have_header = false;
 
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
        cout << "Currently finding a path between " << apair[0] << " and " << apair[1] << "\n";
        outPath = graph.Dijkstra(apair[0], apair[1], weighted); 
        string toWrite = formOutputString(outPath);
        if(toWrite != "") {
          output << toWrite;
        }
        apair.clear();
      }
    }
  } 

  //dummy return value
  output.close();
  f.close();
  return 1;
} 
