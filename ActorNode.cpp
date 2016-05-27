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
  this->source = nullptr;
  this->visited = false;
}

bool ActorNode::isVisited() {
  return this->visited;
}

void ActorNode::visit() {
  this->visited = true;
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
