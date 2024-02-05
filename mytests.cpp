// a file to test certain functions separately as i work
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include "util.h"
using namespace std;

int main(){
  /** PARSE STRING TO WORDS TESTS **/
  // note to self: the below returns the strings in all lowercase
  set<string> testset = parseStringToWords("Hello I'm Bob. I'll go to the cafe!");

  /** SET INTERSECTION AND UNION TESTS **/
  set<string> myset2 = {"A", "B", "C", "D", "E"};
  set<string> myset3 = {"C", "D", "E", "F"};

  set<string> intersectiontest = setIntersection(myset2, myset3); 
  // should print C, D, E
  set<string>::iterator it;
  for(it = intersectiontest.begin(); it != intersectiontest.end(); ++it){
    cout << *it << " ";
  }
  cout << endl;

  set<string> uniontest = setUnion(myset2, myset3); 
  // should print A, B, C, D, E, F
  for(it = uniontest.begin(); it != uniontest.end(); ++it){
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}