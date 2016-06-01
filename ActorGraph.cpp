/*
 * ActorGraph.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/22/2016
 *
 * Class that holds all the methods used to search/build graphs made up of
 * the actors and movies contained in the IMDB database
 */
 
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <tuple>
#include "ActorGraph.hpp"

using namespace std;

/*Comparator class to create a minHeap of Movie* w/ respect to their release year/weight
 * */
bool ActorGraph::minHeapMovie::operator()(Movie*& lhs, Movie*& rhs) const {
  return lhs->getYear() > rhs->getYear();
}

/*Comparator class to create a minHeap of ActorNode* w/ respect to their dist fields
 * */
bool ActorGraph::minHeapActor::operator()(ActorNode*& lhs, ActorNode*& rhs) const {
  return lhs->getDist() > rhs->getDist();
}

ActorGraph::ActorGraph(void) {}

/* Loads in the actors and their movies from in_filename
 * Creates a cast list for every Movie and a list of roles for every Actor
 * Stores movies and actors in their respective unordered_maps
 * */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
  // Initialize the file stream
  ifstream infile(in_filename);

  int numAct = 0;
  int numMov = 0;

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) {
    string s;
  
    // get the next line
    if (!getline( infile, s )) break;
    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
      }
    
      if (record.size() != 3) {
        // we should have exactly 3 columns
        continue;
      }

      string actor_name(record[0]);
      string movie_title(record[1]);
      int movie_year = stoi(record[2]);

      string uniqueTitle = movie_title + to_string(movie_year);
      Movie* currMovie = new Movie(movie_title, movie_year);
      ActorNode* currActor = new ActorNode(actor_name);
  
      // we have an actor/movie relationship, now what?
      // does allActors already contain an ActorNode for this actor?
      int c = allActors.count(actor_name);
      
      //no it does not have it yet
      if(c == 0) {
        //add it to map, update movie in node
        allActors.insert(std::make_pair(actor_name,currActor));
        numAct++;
        //cout << "I'm adding " << actor_name << " to allActors for the first time! \n";
        currActor->addToMovies(uniqueTitle);
      }
      
      //Actor is already in the set
      else {
        //update movie in node
        auto it = allActors.find(actor_name);
        (*it).second->addToMovies(uniqueTitle);
        //cout << (*it).second->getName()  << " was already in allActors \n";

      }

      //Does allMovies already contain this Movie?
      c = allMovies.count(uniqueTitle);
  
      //no it does not have it yet
      if(c == 0) {
        //add it to map, update its cast
        //cout << "I'm adding " << uniqueTitle << " to allMovies for the first time! \n";
        numMov++;
        allMovies.insert(std::make_pair(uniqueTitle, currMovie));
        (*currMovie).addToCast(actor_name);
        //cout << "I added " << actor_name << " to " << uniqueTitle << "'s cast \n";
      }

      //movie already exists
      else {
        //update it's cast
        //cout << uniqueTitle << " was already in allMovies. Updating its cast \n";
        auto it2 = allMovies.find(uniqueTitle);
        //cout << "I added " << actor_name << " to " << uniqueTitle << "'s cast \n";
        (*it2).second->addToCast(actor_name);
      }
  }
  //cout << "Total num of Actors: " << numAct << "\n";
  //cout << "Total num of Movies: " << numMov << "\n";
  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;
}


/* Builds edges linking every actor together by their movies
 * Edges are directed so for every relation, 2 edges exist between the actors
 * */
void ActorGraph::buildGraph() {
  //for every movie in the database
  auto it = allMovies.begin();
  while(it != allMovies.end()) {
    Movie* m = it->second;
    it++;
    vector<string> cast = m->getCast();
    int year = m->getYear();
    string title = m->formUniqueTitle();

    //form edges between every cast member in this movie
    for(int i=0; i < cast.size()-1; i++) {
      ActorNode* a1 = allActors.at(cast[i]);
      for(int j=i+1; j < cast.size(); j++) {
        ActorNode* a2 = allActors.at(cast[j]);
        
        //build 2 edges (one for each actor)
        ActorNode::Edge* e1 = new ActorNode::Edge(a1, a2, m);
        ActorNode::Edge* e2 = new ActorNode::Edge(a2, a1, m);
        a1->addEdge((ActorNode::Edge*)e1);
        a2->addEdge((ActorNode::Edge*)e2);
      }
    } 
  } 
}

/* Finds the weighted path using Dijkstra's algorithm. The more recent the year, 
 * the less weight it has. We want the path with the lowest weight. So ideally
 * our path will have more recent movies.
 * */
vector<pair<string,Movie*>> ActorGraph::Dijkstra(string start, string dest, bool weighted) {
  vector<pair<string,Movie*>> finalPath;
  priority_queue<ActorNode*, vector<ActorNode*>, minHeapActor> pq;
  //stack<ActorNode*> path;
  stack<ActorNode*> toReset;

  bool finished = false;

  //check if start and dest are valid actors
  auto itrCheck = allActors.find(start);
  if(itrCheck == allActors.end()) {
    cout << "ERROR: " << start << " wasn't in the database \n";
    return finalPath;
  }
  itrCheck = allActors.find(dest);
  if(itrCheck == allActors.end()) {
    cout << "ERROR: " << dest << " wasn't in the database \n";
    return finalPath;
  }

  //push start actor onto pq
  ActorNode* startActor = allActors.at(start);
  startActor->updateDist(0);
  pq.push(startActor);
  toReset.push(startActor);

  while(!pq.empty()) {
    ActorNode* c = pq.top();
    pq.pop();
    //check if we have found our destination actor
    if(c->getName() == dest) {
      //cout << "UH OH we found our boy! \n";
      finished = true;
      break;
    }
    //check if actor is already "done"
    if(c->isVisited()) {
      continue;
    } 
    c->visit();
    vector<ActorNode::Edge*> e = c->getEdges();
    //go through all of c's edges
    for(int i=0; i < e.size(); i++) {
      ActorNode::Edge* currEdge = e[i];
      //ActorNode* d = allActors.at(currEdge->getOtherActor(c));
      ActorNode* d = allActors.at(currEdge->getActor2());
      if(d->isVisited()) {
        continue;
      }
      int newWeight;
      if(!weighted) {
        newWeight = c->getDist() + 1;
      }
      else {
        newWeight = c->getDist() + currEdge->getWeight();
      }
      if(newWeight < d->getDist()) {
        d->updateDist(newWeight);
        d->setSource(c);
        d->setSourceMovie(currEdge->getMovie());
        pq.push(d);
        toReset.push(d);
      }
    } 
  }

  //create the final pathway
  ActorNode* c = allActors.at(dest);
  finalPath.push_back(make_pair(dest, nullptr));
  while(c->getSource() != nullptr) {
    //cout << c->getName() << "'s source is: " << c->getSource()->getName() << "\n";
    finalPath.push_back(make_pair(c->getSource()->getName(), allMovies.at(c->getSourceMovie())));
    c = c->getSource();
  }
  reverse(finalPath.begin(),finalPath.end());

  //reset the visited nodes
  clearout(toReset);
  return finalPath;
}

void ActorGraph::clearout(stack<ActorNode*> r) {
  while(!r.empty()) {
    ActorNode* c = r.top();
    r.pop();
    c->updateDist(numeric_limits<int>::max());
    c->unvisit();
    c->setSource(nullptr);
  }
}

/*Build the graph one year at a time, then BFS the actors in the tuple. 
 * This is for a weighted search.
 * */
void ActorGraph::buildBFS(vector<tuple<string,string,int>> &v) {
  //put every movie inside the pq so we can grab them by year
  priority_queue<Movie*, vector<Movie*>, minHeapMovie> pq;
  int i=0;
  auto itr = allMovies.begin();
  while(itr != allMovies.end()) {
    i++;
    pq.push(itr->second);
    itr++;
  }
  cout << i << "\n";
  int currYear;
  Movie* currMovie;
  bool once = true;
  bool stillOneLeft = true;
  while(stillOneLeft && !pq.empty()) {
    int prevYear = pq.top()->getYear();
    while(true) {
      if(pq.empty()) {
        cout<< "we'v exhausted all movies \n";
        break;
      }
      currMovie = pq.top();
      //if this movie is in the current year, build its edges
      if(prevYear == currMovie->getYear()) {
        pq.pop();
        currYear = currMovie->getYear();
        vector<string> cast = currMovie->getCast();
        string title = currMovie->formUniqueTitle();
        //form edges EFFECIENTLY between every cast member in this movie
        //for(int i=0; i < cast.size()-1; i++) {
          ActorNode* a1 = allActors.at(cast[0]);
          for(int j=1; j < cast.size(); j++) {
            ActorNode* a2 = allActors.at(cast[j]);
        
            //build 2 edges (one for each actor)
            ActorNode::Edge* e1 = new ActorNode::Edge(a1, a2, currMovie);
            ActorNode::Edge* e2 = new ActorNode::Edge(a2, a1, currMovie);
            a1->addEdge((ActorNode::Edge*)e1);
            a2->addEdge((ActorNode::Edge*)e2);
          }
        //}
      //if the movie doesn't belong to this year, break
      } else {
        break;
      }
    }
    stillOneLeft = false;
    for(tuple<string,string,int> &tup : v) {
      //check if actors in tuple are valid 
      auto itrCheck = allActors.find(get<0>(tup));
      if(itrCheck == allActors.end()) {
        continue;
      }
      itrCheck = allActors.find(get<1>(tup));
      if(itrCheck == allActors.end()) {
        continue;
      } 
      //if the pair hasn't been linked yet
      if(get<2>(tup) == 9999) {
        vector<pair<string,Movie*>> path = Dijkstra(get<0>(tup), get<1>(tup), false);
        //if pathsize greater than 1, a path has been found
        if(path.size() != 1) {
          get<2>(tup) = currYear;
          cout << "I'm setting " << get<0>(tup) << " and " << get<1>(tup) << "'s connection year to: " << currYear << "\n";
        }
        else {
          stillOneLeft = true;
        }
      }
    } 
    if(!stillOneLeft) {
      break;
    }
  }
}

void ActorGraph::buildUFIND(vector<tuple<string,string,int>> &v) {
  //put every movie inside the pq so we can grab them by year
  cout << "we ufind\n";
  priority_queue<Movie*, vector<Movie*>, minHeapMovie> pq;
  int i=0;
  auto itr = allMovies.begin();
  while(itr != allMovies.end()) {
    i++;
    pq.push(itr->second);
    itr++;
  }
  cout << i << "\n";
  int currYear;
  Movie* currMovie;
  bool once = true;
  bool stillOneLeft = true;
  while(stillOneLeft && !pq.empty()) {
    int prevYear = pq.top()->getYear();
    while(true) {
      if(pq.empty()) {
        cout<< "we'v exhausted all movies \n";
        break;
      }
      currMovie = pq.top();
      //if this movie is in the current year, build its edges
      if(prevYear == currMovie->getYear()) {
        pq.pop();
        currYear = currMovie->getYear();
        vector<string> cast = currMovie->getCast();
        string title = currMovie->formUniqueTitle();
        ActorNode* mergeWith = find(allActors.at(cast[0]));	//this should never fail because every cast has at least 1 actor
        for(int i=1; i < cast.size(); i++) {
          ActorNode* mergeWith2 = find(allActors.at(cast[i]));
          if(mergeWith->getName() != mergeWith2->getName()) {
            mergeWith2->setSource(mergeWith);
          }         
        }
      } else {
        break;
      }
    }
      stillOneLeft = false;     
      for(tuple<string,string,int> &tup : v) {
        auto itrCheck = allActors.find(get<0>(tup));
        if(itrCheck == allActors.end()) {
          continue;
        }
        itrCheck = allActors.find(get<1>(tup));
        if(itrCheck == allActors.end()) {
          continue;
        } 
        if(get<2>(tup) == 9999) {
          if(find(allActors.at(get<0>(tup))) == find(allActors.at(get<1>(tup)))) {
            get<2>(tup) = currYear;
            //cout << "I'm setting " << get<0>(tup) << " and " << get<1>(tup) << "'s connection year to: " << currYear << "\n";
          } else {
            stillOneLeft = true;
          }
        }
      }
    }
  } 


/*A find method to be used in UFIND. It traverses up the tree to find
 * the root (I use the source pointer in my actornode class in a different 
 * way here because I don't want to make two ActorNode pointer member vars
 * when I only use one at a time per method.)
 **/
ActorNode* ActorGraph::find(ActorNode* a) {
  ActorNode* curr = a;
  stack<ActorNode*> reassign;
  while(curr->getSource() != nullptr) {
    reassign.push(curr);
    curr = curr->getSource();
  }
  while(reassign.size() > 1) {
    reassign.top()->setSource(curr);
    reassign.pop();
  }
  
  return curr;
}

double ActorGraph::findAverage(string a) {
  double avg = 0;
  int dist = 1;
  int count = 0;
  int actors_visited = 0;


  //check if a is a valid actor
  auto itrCheck = allActors.find(a);
  if(itrCheck == allActors.end()) {
    cout << "ERROR: " << a << " wasn't in the database \n";
    return 0;
  }

  ActorNode* curr = allActors.at(a);
  priority_queue<ActorNode*, vector<ActorNode*>, minHeapActor> pq;
  queue<ActorNode*> toReset;
  pq.push(curr);  
  toReset.push(curr);  
  curr->updateDist(0);
  int maxDist = 0;


  while(!pq.empty()) {
    curr = pq.top();
    pq.pop();
    
    //check if actor is already "done"
    if(curr->isVisited()) {
      continue;
    } 
    curr->visit();
    actors_visited++;
    vector<ActorNode::Edge*> e = curr->getEdges();
    //go through all of c's edges
    for(int i=0; i < e.size(); i++) {
      ActorNode::Edge* currEdge = e[i];
      //ActorNode* d = allActors.at(currEdge->getOtherActor(curr));
      ActorNode* d = allActors.at(currEdge->getActor2());
      if(d->isVisited()) {
        continue;
      }
      int newWeight;     
      newWeight = curr->getDist() + 1;
      
      if(newWeight < d->getDist()) {
        d->updateDist(newWeight);
        d->setSource(curr);
        d->setSourceMovie(currEdge->getMovie());
        pq.push(d);
        toReset.push(d);
      }
    } 
  }
  stack<ActorNode*> toClear;
  //go through the visited stack to count the average
  while(!toReset.empty()) {
    curr = toReset.front();
    toReset.pop();
    toClear.push(curr);
    if(maxDist < curr->getDist()) {
      maxDist = curr->getDist();
    }

    avg = avg + curr->getDist();
  }
  cout << "we visited: " << actors_visited << "\n";
  avg = avg/(actors_visited-1);	//minus 1 bc we dont want to include the starting actor

  cout << "max distance was: " << maxDist << "\n"; 

  clearout(toClear);

  return avg;
}
