#include "datastore.h"
#include <iostream>

class MyDataStore : public DataStore {
  MyDataStore(){ // constructor

  }

  /**
  * Adds a product to the data store
  */
  void addProduct(Product* p){

  }

  /**
  * Adds a user to the data store
  */
  void addUser(User* u){

  }
  /**
  * Adds a user to the data store
  */
  void addUser(User* u){

  }

  /**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
  std::vector<Product*> search(std::vector<std::string>& terms, int type){

  }

  /**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
  std::vector<Product*> search(std::vector<std::string>& terms, int type){

  }

  /**
  * Reproduce the database file from the current Products and User values
  */
  void dump(std::ostream& ofile){

  }

  ~MyDataStore(){
    cout << "deleting mydatastore object\n";
  }
}