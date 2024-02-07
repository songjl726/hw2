#ifndef CLOTHING_H
#define CLOTHING_H
#include <set>
#include <string>
#include <iostream>
#include "product.h"
#include "util.h"

class Clothing : public Product {
public:
  Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
  ~Clothing();
  
  /**
     * Returns the appropriate keywords that this product should be associated with
     */
  std::set<std::string> keywords() const;

  /**
    * Returns a string to display the product info for hits of the search
    */
  std::string displayString() const;

private:
  std::string size_;
  std::string brand_;
};

#endif