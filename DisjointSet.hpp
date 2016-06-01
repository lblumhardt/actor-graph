/*
 * DisjointSet.hpp
 * Author: Lucas Blumhardt A12020745 
 * Date:   5/30/2016
 *
 * Class made to union disjoint sets and find the oldest path between two actors
 */

#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP
#include <iostream>
#include <set>
#include <unordered_map>
#include "ActorNode.hpp"

using namespace std;

class DisjointSet{
private:
  //member vars
  ActorNode* head;
  int size;
  unordered_map<string, ActorNode*> contents;

public:
  DisjointSet(ActorNode* h);

  DisjointSet* merge(DisjointSet *u);

  ActorNode* find(ActorNode* a);
};


#endif // DISJOINTSET_HPP
