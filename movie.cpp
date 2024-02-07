#include <iostream>
#include <string>
#include <set>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
  Product(category, name, price, qty) 
{
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie(){
  
}

std::set<std::string> Movie::keywords() const {
  // parse the title of the Movie and the genre into two sets
  set<string> namewords = parseStringToWords(name_);
  set<string> genrewords = parseStringToWords(genre_);

  // combining the two parsed sets into one set, which will be returned
  set<string> result = setUnion(namewords, genrewords);

  return result;
}

std::string Movie::displayString() const {
  // yes this is probably the dumbest way you could go about this but... it works
  string result = name_;
  result += "\n";
  result += "Genre: ";
  result += genre_;
  result += " Rating: ";
  result += rating_;
  result += "\n";
  result += price_;
  result += + " "; 
  result += qty_;
  result += " left.";
  return result;
}
