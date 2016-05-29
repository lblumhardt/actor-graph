/*
 * Edge.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/24/2016
 * 
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Edge.hpp"

using namespace std;

Edge::Edge(ActorNode* a1, ActorNode* a2, Movie* mov) {
  this->a1 = a1;
  this->a2 = a2;
  this->movie = mov; 
}

string Edge::getActor1() {
  return this->a1->getName();
}

string Edge::getActor2() {
  return this->a2->getName();
}

string Edge::getMovie() {
  return this->movie->formUniqueTitle();
}

int Edge::getWeight() {
  int year = this->movie->getYear();
  return 1 + (2015 - year);
}

int Edge::getYear() {
  return this->movie->getYear();
}
