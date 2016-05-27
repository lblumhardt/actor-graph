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
#include "Edge.hpp"
#include <unordered_map>
#include <utility>
#include <vector>

// Maybe include some data structures here

using namespace std;

class ActorGraph {
  
  class ActorNodeComp {  
    
    public:
    
      bool operator()(ActorNode* p1, ActorNode* p2) const;
  };

  class MovieComp {
    
    public:
  
      bool operator()(Movie* m1, Movie* m2) const;
  };


protected:

  unordered_map<string, ActorNode*> allActors;
  unordered_map<string, Movie*> allMovies;
    

public:
    ActorGraph(void);

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
  //main method used to find a path between two actors
  vector<pair<string,Movie*>> uBFS(string start, string dest);
};


#endif // ACTORGRAPH_HPP
