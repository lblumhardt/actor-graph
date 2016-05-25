/*
 * Edge.hpp
 * Author: Lucas Blumhardt A12020745 
 * Date:   5/24/2016
 *
 * Edge used to link two ActorNodes by a Movie
 */

#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>
#include <set>
#include "ActorNode.hpp"
#include "Movie.hpp"

using namespace std;

class Edge {
private:
  //member vars
  ActorNode* a1;
  ActorNode* a2;
  Movie* movie;

public:
  Edge(ActorNode* a1, ActorNode* a2, Movie* mov);

  //getter declarations
  string getActor1();

  string getActor2();

  string getMovie();  
};


#endif // EDGE_HPP
