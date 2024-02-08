#include <iostream>
#include <string>
#include <set>
#include "book.h"

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

  return result;
}

std::string Book::displayString() const {
  // yes this is probably the dumbest way you could go about this but... it works
  string result = name_;
  result += "\n";
  result += "Author: ";
  result += author_;
  result += " ISBN: ";
  result += isbn_;
  result += "\n";
  result += price_;
  result += + " "; 
  result += qty_;
  result += " left.";
  return result;
}


void Book::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}