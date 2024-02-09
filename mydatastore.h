#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "user.h"
#include "product.h"
#include <queue>
#include <set>
#include <vector>
#include <map>
#include <iostream>

class MyDataStore : public DataStore {
public:
  // constructor
  MyDataStore();

  /**
  * Adds a product to the data store
  */
  void addProduct(Product* p);

  /**
  * Adds a user to the data store
  */
  void addUser(User* u);

  /**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  /**
  * Reproduce the database file from the current Products and User values
  */
  void dump(std::ostream& ofile);

  // destructor
  ~MyDataStore();

  // functions that I'm adding on my own (not part of parent class)
  // these are all based on the commands in the menu
  void addToCart(std::string uname, int hitnum);
  void viewCart(std::string uname);
  void buyCart(std::string uname);

private:
  std::map<std::string, User*> userMap_;
  std::set<Product*> prodSet_;
  std::map<std::string, std::queue<Product*>> userCartMap_;
  std::map<std::string, std::set<Product*>> keywordProdMap_;
};

#endif