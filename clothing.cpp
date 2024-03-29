#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
  Product(category, name, price, qty) 
{
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing(){
  
}

std::set<std::string> Clothing::keywords() const {
  // parse the title of the clothing and the brand name into two sets
  set<string> namewords = parseStringToWords(name_);
  set<string> brandwords = parseStringToWords(brand_);

  // combining the two parsed sets into one set, which will be returned
  set<string> result = setUnion(namewords, brandwords);

  return result;
}

std::string Clothing::displayString() const {
  // fixed the implementation so it actually works ELL OH ELL
  stringstream result;
  result << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return result.str();
}

void Clothing::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}