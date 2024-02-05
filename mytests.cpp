// a file to test certain functions separately as i work
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include "util.h"
using namespace std;

int main(){
  set<string> testset = parseStringToWords("Hello I'm Bob. I'll go to the cafe!");
  return 0;
}