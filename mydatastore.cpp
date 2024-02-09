#include <iostream>
#include "datastore.h"
#include "mydatastore.h"

// 2 maps
  // one is string of a keyword (e.g. "Men") to a set of Products that have that keyword
  // one is a string of the username (e.g. "Tommy Trojan") to a queue of Products in their cart

using namespace std;

// constructor
MyDataStore::MyDataStore(){

}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p){
  // add product to sets in the keywordProduct map based on its keywords
  prodSet_.insert(p);

  // get all the keywords of the current product
  set<string> currProdKeywords = p->keywords();

  // go over all the  keywords in the current product's set of keywords
  set<string> iterator it;
  for(it = currProdKeywords.begin(); it != currProdKeywords.end(); ++it){
    // only insert if the keyword DOESN'T already exist in the map
    if(keywordProdMap_.find(*it) == keywordProdMap_.end()){
      set<Product*> currProdSet;
      currProdSet.insert(p);
      keywordProdMap_.insert(make_pair(*it, currProdSet));
    } else {
      // if the keyword already exists, 
      // just add the product into the set mapped to it
      keywordProdMap_[*it].insert(p);
    }
  }
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
  // add it to map of string to User*s 
  string currUname = u->getName();
  if(userMap_.find(currUname) == userMap_.end()){
    userMap_.insert(make_pair(currUname, u));
  }

  // add name string of the user and empty cart queue to the userCartMap
  // but ONLY if this user is NOT already in the userCartMap
  if(userCartMap_.find(currUname) == userCartMap_.end()){
    queue<Product*> currCart;
    userCartMap_.insert(make_pair(currUname, currCart));    
  }
}


/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  if(type == 0){
    
  } else { // type is 1
    
  }
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){

}

// add a product to a user's cart given the username and hit number
void MyDataStore::addToCart(std::string uname, int hitnum){

}

// display a user's cart given the username
void MyDataStore::viewCart(std::string uname){

}

// buy the Products in a user's cart if they can afford it, given a username
void MyDataStore::buyCart(std::string uname){

}

// destructor
MyDataStore::~MyDataStore(){

}