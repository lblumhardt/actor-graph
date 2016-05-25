/*
 * ActorNode.hpp
 * Author: Lucas Blumhardt A12020745 
 * Date:   5/23/2016
 *
 * Nodes used in the graphs made during pathFind (Union/Find)
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <set>
#include "Movie.hpp"

using namespace std;

class ActorNode {
private:
  //member vars
  string name;
  set<string> movies;	//movies this actor has starred in
  ActorNode* source;
  string sourceMovie;
  bool visited;

public:
  ActorNode(string name);

  //getter declarations
  string getName();

  set<string> getMovies();
  
  //mutator declarations
  bool addToMovies(string movieToAdd);
 
  bool isVisited();

  void visit(); 

  void setSource(ActorNode* s);

  ActorNode* getSource();

  void setSourceMovie(string s);

  string getSourceMovie();
};


#endif // ACTORNODE_HPP
