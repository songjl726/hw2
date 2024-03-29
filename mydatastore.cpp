#include <iostream>
#include "mydatastore.h"
#include "util.h"
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
  set<string>::iterator it;
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
  // add it to set of User*s (only used during dump)
  userSet_.insert(u);

  // add it to map of string to User*s 
  // make it lowercase so it's case insensitive
  string currUname = convToLower(u->getName());
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
  // make a big string of all the strings in the given vector terms
  // so i can parse it into words with my function
  string combinedTerms = "";
  for(size_t i = 0; i < terms.size() - 1; i++){
    combinedTerms += terms[i] + " ";
  }
  combinedTerms += terms[terms.size()-1];

  // call parseStringToWords on this big one
  set<string> parsedTerms = parseStringToWords(combinedTerms);
  set<string>::iterator it;

  vector<Product*> result;
  set<Product*> almostResult;
  if(type == 0){
    // AND search means that it must have all terms. so just use the first
    for (it = parsedTerms.begin(); it != parsedTerms.end(); ++it){
      map<string, set<Product*>>::iterator mapit = keywordProdMap_.find(*it);
      if (mapit != keywordProdMap_.end()) {
        set<Product*> temp = keywordProdMap_[*it];

        if (almostResult.empty()){
          almostResult = keywordProdMap_[*it];
        } else {
          set<Product*> andedSet = setIntersection(almostResult, temp);
          almostResult = andedSet;
        }
      }
    }
  } else if (type == 1) { 
    // OR search means return all the products that have ANY of the terms
    for(it = parsedTerms.begin(); it != parsedTerms.end(); ++it){
      // only return stuff if the keyword even exists in the map
      map<string, set<Product*>>::iterator mapit = keywordProdMap_.find(*it);
      if (mapit != keywordProdMap_.end()){
        set<Product*> temp = keywordProdMap_[*it];
        almostResult = setUnion(almostResult, temp);
      }
    }
  }

  // convert the result set to a vector to be returned if there were hits
  if (!almostResult.empty()){
    set<Product*>::iterator it;
    for(it = almostResult.begin(); it != almostResult.end(); ++it){
      result.push_back(*it);
    }
  }

  return result;
}

// add a product to a user's cart given the username and hit number
void MyDataStore::addToCart(std::string uname, Product* p){
  uname = convToLower(uname);
  // check if username entered is valid, if not, stop the function
  if (userCartMap_.find(uname) == userCartMap_.end()){
    cout << "Invalid request" << endl;
    return;
  }

  userCartMap_[uname].push(p);
}

// display a user's cart given the username
void MyDataStore::viewCart(std::string uname){
  uname = convToLower(uname);
  // check if username entered is valid, if not, stop the function
  if (userCartMap_.find(uname) == userCartMap_.end()){
    cout << "Invalid username" << endl;
    return;
  }

  int counter = 1;
  queue<Product*> cartCopy = userCartMap_[uname];
  while (!cartCopy.empty()) {
    // print a call displayString() on the front Product
    cout << "Item " << counter << "\n";
    cout << cartCopy.front()->displayString() << endl;
    cartCopy.pop(); // remove the front element
    counter++; // increment the counter so the next item is a number higher
  }
}

// buy the Products in a user's cart if they can afford it, given a username
void MyDataStore::buyCart(std::string uname){
  uname = convToLower(uname);
  // check if username entered is valid, if not, stop the function
  if (userCartMap_.find(uname) == userCartMap_.end()){
    cout << "Invalid username" << endl;
    return;
  }
  
  // initialize another queue for the leftover items that the user CAN'T buy
  queue<Product*> cartLeftover; 
  // get the user's starting balance
  double currBalance = (userMap_[uname])->getBalance();
  while(!userCartMap_[uname].empty()){
    Product* currProd = userCartMap_[uname].front();
    double currProdPrice = currProd->getPrice();
    int currProdQty = currProd->getQty();
    if(currBalance <= 0 || currBalance < currProdPrice || currProdQty <= 0){ // the user CAN'T buy it
      cartLeftover.push(currProd);
    } else {                                            // the user CAN buy it
      // update the actual data members of the actual objects
      (userCartMap_[uname].front())->subtractQty(1);
      (userMap_[uname])->deductAmount(currProdPrice);
      currBalance = (userMap_[uname])->getBalance();
    }
    userCartMap_[uname].pop(); // remove the front product, it has been dealt with
  }

  // replace the user's cart with the updated one (leftovers)
  userCartMap_[uname] = cartLeftover;
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){
  // products section first
  ofile << "<products>" << endl;
  set<Product*>::iterator it1;
  for(it1 = prodSet_.begin(); it1 != prodSet_.end(); ++it1){
    (*it1)->dump(ofile);
  }
  ofile << "</products>" << endl;

  // users section next
  ofile << "<users>" << endl;
  set<User*>::iterator it2;
  for(it2 = userSet_.begin(); it2 != userSet_.end(); ++it2){
    (*it2)->dump(ofile);
  }
  ofile << "</users>" << endl;
}

// destructor
MyDataStore::~MyDataStore(){
  // deleting the userSet_
  for(set<User*>::iterator it = userSet_.begin(); it != userSet_.end(); ++it){
    delete *it;
  }

  // deleting the prodSet_
  for(set<Product*>::iterator it = prodSet_.begin(); it != prodSet_.end(); ++it){
    delete *it;
  }
}