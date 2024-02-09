#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
  Product(category, name, price, qty) 
{
  isbn_ = isbn;
  author_ = author;
}

Book::~Book(){
  
}

std::set<std::string> Book::keywords() const {
  // parse the title of the book and the author name into two sets
  set<string> namewords = parseStringToWords(name_);
  set<string> authorwords = parseStringToWords(author_);

  // combining the two parsed sets into one set, which will be returned
  set<string> result = setUnion(namewords, authorwords);

  // add in the full isbn without parsing
  result.insert(isbn_); 

  // cout << "parsed book keywords:" << endl;
  // for(set<string>::iterator it = result.begin(); it != result.end(); ++it){
  //   cout << *it << " ";
  // }
  // cout << endl;

  return result;
}

std::string Book::displayString() const {
  // fixed the implementation so it actually works ELL OH ELL
  stringstream result;
  result << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return result.str();
}


void Book::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}