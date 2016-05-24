/*
 * ActorNode.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/23/2016
 * 
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorNode.hpp"

using namespace std;

ActorNode::ActorNode(string name) {
  this->name = name;
}

string ActorNode::getName() {
  return this->name;
}

set<Movie*> ActorNode::getMovies() {
  return this->movies;
}

bool ActorNode::addToMovies(Movie* movieToAdd) {
  auto tempPair = this->movies.insert(movieToAdd);
  return tempPair.second;
}
