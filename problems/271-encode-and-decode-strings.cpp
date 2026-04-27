#include "testSuite.h"
#include <vector>

using namespace std;

/// @problem
///
/// Design an algorithm to encode a list of strings to a string. The encoded
/// string is then sent over the network and is decoded back to the original
/// list of strings.
///
///
/// @constrains
///
/// @solution 1

inline const string deliminting{"##"};

string Encode(vector<string> &strs) {

  string result;

  for (size_t i{0}; i < strs.size(); i++) {
    result.append(strs[i]);
    result.append(deliminting);
  }

  return result;
}

vector<string> Decode(string str) {
  vector<string> parts;
  size_t start{0};

  auto end = str.find(deliminting, start);

  while (end != string::npos) {
    parts.emplace_back(str.substr(start, end - start));
    start = end + deliminting.length();
    end = str.find(deliminting, start);
  }

  return parts;
}

int main() {
  vector<string> str{"Hello, ", "World"};
  ExpectEq(str, Decode(Encode(str)));

  str = {"13DFDAF3242!@#@!, ", "World"};
  ExpectEq(str, Decode(Encode(str)));

  str = {"Hello, ", "34242$$1232"};
  ExpectEq(str, Decode(Encode(str)));
}
