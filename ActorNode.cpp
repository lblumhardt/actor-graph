/*
 * ActorNode.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/23/2016
 * 
 */
 
#include <fstream>
#include <limits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorNode.hpp"

using namespace std;

//Edge constructor
ActorNode::Edge::Edge(ActorNode* a1, ActorNode* a2, Movie* mov) {
  this->a1 = a1;
  this->a2 = a2;
  this->movie = mov; 
}

//never used. Should return first actor
string ActorNode::Edge::getActor1() {
  return this->a1->getName();
}

//returns the second(dest) actor
ActorNode* ActorNode::Edge::getActor2() {
  return this->a2;
}

//gets the edge's movie title
string ActorNode::Edge::getMovie() {
  return this->movie->formUniqueTitle();
}

//get the edges weight (for weighted bfs)
int ActorNode::Edge::getWeight() {
  int year = this->movie->getYear();
  return 1 + (2015 - year);
}

//gets the edge's year
int ActorNode::Edge::getYear() {
  return this->movie->getYear();
}

//ActorNode constructor
ActorNode::ActorNode(string name) {
  this->name = name;
  this->source = nullptr;
  this->visited = false;
  this->dist = numeric_limits<int>::max();
}

//ActorNode destructor
ActorNode::~ActorNode() {
  this->deleteEdges();
  delete this;
}

//checks if actorNode is visited
bool ActorNode::isVisited() {
  return this->visited;
}

//visits the actorNode
void ActorNode::visit() {
  this->visited = true;
  return;
}

//resets the visited flag
void ActorNode::unvisit() {
  this->visited = false;
  return;
}

//gives the actor's name
string ActorNode::getName() {
  return this->name;
}

//gives the actor's movies
vector<string> ActorNode::getMovies() {
  return this->movies;
}

//adds the movie to the actor's starred in list
bool ActorNode::addToMovies(string movieToAdd) {
  this->movies.push_back(movieToAdd);
  return true;
}

//sets the source/parent node (parent for UFIND, source for Dijkstras)
void ActorNode::setSource(ActorNode* s) {
  this->source = s;
  return;
}

//gets the source/parent node
ActorNode* ActorNode::getSource() {
  return this->source;
}

//sets the source movie
void ActorNode::setSourceMovie(string s) {
  this->sourceMovie = s;
  return;
}

//gets the source movie
string ActorNode::getSourceMovie() {
  return this->sourceMovie;
}

//gets the edges in this actorNode
vector<ActorNode::Edge*> ActorNode::getEdges() { 
  return this->edges;
}

//adds an edge to this actornOde
void ActorNode::addEdge(ActorNode::Edge* e) {
  this->edges.push_back(e);
}

//updates the actor's distance (for Dijkstras)
void ActorNode::updateDist(int d) {
  this->dist = d;
  return;
}

//gets the distance (for Dijkstras)
int ActorNode::getDist() {
  return this->dist;
}

//deletes all this actors edges
void ActorNode::deleteEdges() {
  int start = this->edges.size() - 1;
  for(start; start >= 0; start--) {
    delete this->edges[start];
  }
  return;
}
