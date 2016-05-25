/*
 * ActorGraph.cpp
 * Author: Lucas Blumhardt A12020745
 * Date:   5/22/2016
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include "ActorGraph.hpp"

using namespace std;

ActorGraph::ActorGraph(void) {}

/*
//comparator used for the set of ActorNode pointers allActors
bool ActorGraph::ActorNodeComp::operator()(ActorNode* p1, ActorNode* p2) const {
  return (*p1).getName() < (*p2).getName();
}

bool operator()(Movie* m1, Movie* m2) const {
  
}
*/


bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
  // Initialize the file stream
  ifstream infile(in_filename);

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
        //cout << "I'm adding " << actor_name << " to allActors for the first time! \n";
        currActor->addToMovies(uniqueTitle);
      }
      
      //Actor is already in the set
      else {
        //update movie in node
        //cout << actor_name << " was already in allActors \n";
        auto it = allActors.find(actor_name);
        (*it).second->addToMovies(uniqueTitle);
      }

      //Does allMovies already contain this Movie?
      c = allMovies.count(uniqueTitle);
  
      //no it does not have it yet
      if(c == 0) {
        //add it to map, update its cast
        //cout << "I'm adding " << uniqueTitle << " to allMovies for the first time! \n";
        allMovies.insert(std::make_pair(uniqueTitle, currMovie));
        (*currMovie).addToCast(actor_name);
        cout << "I added " << actor_name << " to " << uniqueTitle << "'s cast \n";
      }

      //movie already exists
      else {
        //update it's cast
        //cout << uniqueTitle << " was already in allMovies. Updating its cast \n";
        auto it2 = allMovies.find(uniqueTitle);
        cout << "I added " << actor_name << " to " << uniqueTitle << "'s cast \n";
        (*it2).second->addToCast(actor_name);
      }
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;
}

void ActorGraph::findPath(string start, string dest) {
  bool done = false;
  //check if actors are represented in allActors
  auto tempitr = allActors.find(start);
  if(tempitr == allActors.end()) {
    cout << start << " was NOT found in the database. Exiting. \n";
    return;
  }
  ActorNode* startNode = (*tempitr).second;  
   
  tempitr = allActors.find(dest);
  if(tempitr == allActors.end()) {
    cout << dest << " was NOT found in the database. Exiting. \n";
    return;
  }
  ActorNode* destNode = (*tempitr).second;
  
  //first check is to see if these two actors are only 1 step away
  set<string> m1 = startNode->getMovies();
  set<string> m2 = destNode->getMovies();
  string currMovie = "";
  auto itr1 = m1.begin();
  auto itr2 = m2.begin();
  while(itr1 != m1.end()) {
    currMovie = (*itr1);
    //cout << start << " starred in " << currMovie << "\n";
    itr1++;
    itr2 = m2.begin();
    while(itr2 != m2.end()) {
      //cout << dest << " starred in " << (*itr2)->formUniqueTitle() << "\n";
      if(currMovie == (*itr2)) {
        cout << start << " and " << dest << " stared in " << currMovie << " together!! \n";
      }
      itr2++; 
    }
  }
  
  queue<Movie*> moviesToExplore;
  queue<ActorNode*> actorsToExplore;
  ActorNode* currActor; 
  Movie* currMovieP;
  ActorNode* castMem;

  actorsToExplore.push(startNode);
  //explore actors and their films one at a time
  while(!actorsToExplore.empty()) {
    currActor = actorsToExplore.front();
    actorsToExplore.pop();
    
    //if we already visited this actor, ignore it
    if(currActor->isVisited()) {
      continue;
    } 
    currActor->visit();
    
    //explore this actors movies
    auto movieitr = currActor->getMovies().begin();
    while(movieitr != currActor->getMovies().end()) {
 
      currMovie = *movieitr;
      movieitr++;
      cout << currActor->getName() << " was in " << currMovie << "\n";
      currMovieP = allMovies.at(currMovie);
      
      //ignore movies that we've visited the cast of
      if(currMovieP->isVisited()) {
        continue;
      }
      currMovieP->visit();
      set<string> cast = currMovieP->getCast();
      
      cout << "CURRENTLY VISITING " << currMovie << "\n";
      cout << "IT'S CAST IS AS FOLLOWS: \n";

      //loop through to see if this movie matches any of dest's movies
      itr2 = m2.begin();
      while(itr2 != m2.end()) {
        if(currMovie == (*itr2)) {
          //this actor starred in a film with our dest actor
          cout << "CONNECTION FOUND! \n";
          destNode->setSource(currActor);  
          destNode->setSourceMovie(currMovie);
          done = true;
          break;
        }
        itr2++; 
      }
      if(done) {
        cout << "we broke out like a bat outta heck \n";
        break;
      } 
       
      //A link wasn't found with this movie, so enqueue the cast
      
      //set<string> cast = (*movieitr)->getCast();
      
      //set every castmember's source to currActor before enqueuing
      auto castitr = cast.begin();
      while(castitr != cast.end()) {
        cout << "entered the cast \n";
        string actorName = *castitr;
        auto tempItr = allActors.find(actorName);
        castMem = tempItr->second;
        cout << actorName << " is in the cast \n";
        if(castMem->isVisited()) {
          castitr++;
          continue;
        }  
        cout << "setting " << actorName << " source actor to " << currActor->getName() << "\n";
        castMem->setSource(currActor);
        cout << "setting " << actorName << " source movie to " << currMovie << "\n";
        castMem->setSourceMovie(currMovie);
        actorsToExplore.push(castMem); 
        castitr++;
      } 
    } 
    if(done) {
      break;
    }
  }
  cout << "made it out of ht ewhile loop \n"; 
  //We have found the shortest path. Now to turn the path into a vector
  vector<pair<string,string>> pathway;
  pathway.push_back(make_pair(destNode->getName(),""));
  currActor = destNode;
  while(currActor->getSource() != nullptr) {
    pathway.push_back(make_pair(currActor->getSource()->getName(),currActor->getSourceMovie()));
    currActor = currActor->getSource();
  }
  
  //lets print to see the path in reverse
  for(int i = 0; i < pathway.size(); i++) {
    auto pear = pathway[i];
    cout << pear.first << " --> " << pear.second << "\n";
  }
  return;
}
