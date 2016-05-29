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


ActorNode::Edge::Edge(ActorNode* a1, ActorNode* a2, Movie* mov) {
  this->a1 = a1;
  this->a2 = a2;
  this->movie = mov; 
}

string ActorNode::Edge::getActor1() {
  return this->a1->getName();
}

string ActorNode::Edge::getActor2() {
  return this->a2->getName();
}

string ActorNode::Edge::getMovie() {
  return this->movie->formUniqueTitle();
}

int ActorNode::Edge::getWeight() {
  int year = this->movie->getYear();
  return 1 + (2015 - year);
}

int ActorNode::Edge::getYear() {
  return this->movie->getYear();
}

ActorNode::ActorNode(string name) {
  this->name = name;
  this->source = nullptr;
  this->visited = false;
  this->dist = numeric_limits<int>::max();
}

bool ActorNode::isVisited() {
  return this->visited;
}

void ActorNode::visit() {
  this->visited = true;
  return;
}

void ActorNode::unvisit() {
  this->visited = false;
  return;
}

string ActorNode::getName() {
  return this->name;
}

vector<string> ActorNode::getMovies() {
  return this->movies;
}

bool ActorNode::addToMovies(string movieToAdd) {
  this->movies.push_back(movieToAdd);
  return true;
}

void ActorNode::setSource(ActorNode* s) {
  this->source = s;
  return;
}

ActorNode* ActorNode::getSource() {
  return this->source;
}

void ActorNode::setSourceMovie(string s) {
  this->sourceMovie = s;
  return;
}

string ActorNode::getSourceMovie() {
  return this->sourceMovie;
}

vector<ActorNode::Edge*> ActorNode::getEdges() { 
  return this->edges;
}

void ActorNode::addEdge(ActorNode::Edge* e) {
  this->edges.push_back(e);
}

void ActorNode::updateDist(int d) {
  this->dist = d;
  return;
}

int ActorNode::getDist() {
  return this->dist;
}
