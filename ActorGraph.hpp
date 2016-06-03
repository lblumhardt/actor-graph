/*
 * ActorGraph.hpp
 * Author: Lucas Blumhardt A12020745 
 * Date:   5/22/2016
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include "ActorNode.hpp"
#include "Movie.hpp"
#include <unordered_map>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

class ActorGraph {
  
  //comparator class for a min Heap of movies (w/ respect to release year)
  class minHeapMovie {
    public:
      
      bool operator()(Movie*& lhs, Movie*& rhs) const;
  };

  //comparator class for a min heap of Actors (w/ respect to their dist fields)
  class minHeapActor {
    public:
 
      bool operator()(ActorNode*& lhs, ActorNode*& rhs) const;
  };

protected:

  unordered_map<string, ActorNode*> allActors;
  unordered_map<string, Movie*> allMovies;
    
public:
  ActorGraph(void);

  ~ActorGraph();

  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
  void buildBFS(vector<tuple<string,string,int>> &v);

  void buildUFIND(vector<tuple<string,string,int>> &v);

  void buildGraph();

  vector<pair<string,Movie*>> Dijkstra(string start, string dest, bool weighted); 

  void clearout(stack<ActorNode*> r);

  ActorNode* find(ActorNode* a); 

  double findAverage(string a); 

};
#endif // ACTORGRAPH_HPP
