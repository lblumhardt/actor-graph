/*
 * Movie.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/23/2016
 * 
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Movie.hpp"

using namespace std;

Movie::Movie(string title, int year) {
  this->title = title;
  this->year = year;
  this->visited = false;
}

string Movie::formUniqueTitle() {
  return this->title + to_string(this->year); 
}

string Movie::getTitle() {
  return this->title;
}

int Movie::getYear() {
  return this->year;
}

vector<string> Movie::getCast() {
  return this->cast;
}

bool Movie::addToCast(string actor) {
  this->cast.push_back(actor);
  return true;
}

bool Movie::isVisited() {
  return this->visited;
}

void Movie::visit() {
  this->visited = true;
}
