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
  set<Movie*> movies;	//movies this actor has starred in

public:
  ActorNode(string name);

  //getter declarations
  string getName();

  set<Movie*> getMovies();
  
  //mutator declarations
  bool addToMovies(Movie* movieToAdd);
  
};


#endif // ACTORNODE_HPP
