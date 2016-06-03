/*
 * Movie.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/23/2016
 * 
 * This class stores the relation (what we use to build edges) between
 * ActorNodes
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Movie.hpp"

using namespace std;

//Movie ctor
Movie::Movie(string title, int year) {
  this->title = title;
  this->year = year;
  this->visited = false;
}

//combines the title and year to form a unique key
string Movie::formUniqueTitle() {
  return this->title + to_string(this->year); 
}

//returns just the title. I don't believe this is ever used
string Movie::getTitle() {
  return this->title;
}

//returns the year of this movie
int Movie::getYear() {
  return this->year;
}

//returns every Actor that has been in this movie
vector<string> Movie::getCast() {
  return this->cast;
}

//adds an actor to the cast list
bool Movie::addToCast(string actor) {
  this->cast.push_back(actor);
  return true;
}

//checks if we have visited this movie before: UNUSED
bool Movie::isVisited() {
  return this->visited;
}

//visits this movie: UNUSED
void Movie::visit() {
  this->visited = true;
}
