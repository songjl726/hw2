#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

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
  // fixed the implementation so it actually works ELL OH ELL
  stringstream result;
  result << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return result.str();
}

void Movie::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}