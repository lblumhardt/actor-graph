/*
 * Movie.hpp
 * Author: Lucas Blumhardt A12020745 
 * Date:   5/23/2016
 *
 * Movie object that actorNodes will point to. Will have a list of all movies in ActorGraph
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP
#include <iostream>
#include <set>

using namespace std;

class Movie{
private:
  //member vars
  string title;
  int year;
  set<string> cast;

public:
  Movie(string title, int year);

  string formUniqueTitle(); 

  //getter declarations
  string getTitle();

  int getYear();

  set<string> getCast();
  
  //mutator declarations
  bool addToCast(string actor);

  
};


#endif // MOVIE_HPP