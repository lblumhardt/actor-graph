
#include <utility>
#include "DisjointSet.hpp"

using namespace std;

DisjointSet::DisjointSet(ActorNode* h) {
  this->head = h;
  contents.insert(make_pair(h->getName(),h));
  this->size = 1;
}

DisjointSet* DisjointSet::merge(DisjointSet *u) {
  //merge into the param set
  if(this->size < u->size) {
    this->head->setSource(u->head);
    this->head = u->head;
    u->size = this->size + u->size;
    u->contents.insert(this->contents.begin(), this->contents.end());
    delete this;
    return u;
  }
  
  //merge into the calling obj set
  else {
    u->head->setSource(this->head);
    u->head = this->head;
    this->size = this->size + u->size;
    this->contents.insert(u->contents.begin(), u->contents.end());
    delete u;
    return this;
  }  
}

ActorNode* DisjointSet::find(ActorNode* a) { 
  return this->head;
}
