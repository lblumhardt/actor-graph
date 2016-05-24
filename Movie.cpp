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

set<string> Movie::getCast() {
  return this->cast;
}

bool Movie::addToCast(string actor) {
  auto tempPair = this->cast.insert(actor);
  return tempPair.second;
}
