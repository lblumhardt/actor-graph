/*
 * ActorNode.hpp
 * Author: Lucas Blumhardt A12020745 
 * Date:   5/23/2016
 *
 * Nodes used in the graphs made during pathFind (Union/Find)
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <set>
#include <vector>
//#include "Edge.hpp"
#include "Movie.hpp"

using namespace std;

class ActorNode {

public:

  class Edge {
    private:
      //member vars
      ActorNode* a1;
      ActorNode* a2;
      Movie* movie;

    public:
      Edge(ActorNode* a1, ActorNode* a2, Movie* mov);
  
      //getter declarations
      string getActor1();

      ActorNode* getActor2();

      string getOtherActor(ActorNode* a);

      string getMovie();  

      int getWeight();

      int getYear();
  };

 
  ActorNode(string name);

  ~ActorNode();

  //getter declarations
  string getName();

  vector<string> getMovies();
  
  //mutator declarations
  bool addToMovies(string movieToAdd);
 
  bool isVisited();

  void visit(); 
 
  void unvisit();

  void setSource(ActorNode* s);

  ActorNode* getSource();

  void setSourceMovie(string s);

  string getSourceMovie();

  vector<Edge*> getEdges();

  void addEdge(Edge* e);

  void updateDist(int d);

  int getDist();

  void deleteEdges();

private:
  
  //member vars
  string name;
  vector<string> movies;	//movies this actor has starred in
  vector<Edge*> edges;
  ActorNode* source;		//to be used differently in UnionFind and BFS
  string sourceMovie;
  bool visited;
  int dist; 
};


#endif // ACTORNODE_HPP
