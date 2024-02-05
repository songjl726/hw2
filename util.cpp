#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> result;
  // convert the input to all lowercase for comparison ease later
  std::string lower = convToLower(rawWords); 

  // loop through the rawWords to deal with punctuation
  for(size_t i=0; i<lower.length(); i++){
    // replace the apostrophes with spaces so parsing works as intended
    if (lower[i] == '\''){
      lower[i] = ' ';
    } else if (ispunct(lower[i])){
      // remove all other punctuation
      lower.erase(i, 1);
    }
  }

  // cout << "lower: " << lower << endl;
 
  stringstream ss(lower);
  std::string word;

  while (ss >> word){
    // skip the current keyword if it's too short
    if (word.length() >= 2){
      // insert the word into the set
      result.insert(word);
      // cout << "inserting: " << word << endl;
    }
  }
  return result;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
