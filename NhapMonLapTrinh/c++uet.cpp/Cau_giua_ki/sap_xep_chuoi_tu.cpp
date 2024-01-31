#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main() {
      pair<  string, char> phrases[4] = {{"", 'A'}, {"", 'B'}, {"", 'C'}, {"", 'D'}};

    // Read the input phrases
    for (int i = 0; i < 4; ++i) {
          getline(  cin, phrases[i].first);
    }

    // Sort the phrases in lexicographical order
      sort(phrases, phrases + 4);

    // Print the sorted phrases
    for (int i = 0; i < 4; ++i) {
          cout << phrases[i].second << ' ';
    }

    return 0;
}