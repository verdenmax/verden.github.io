#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  set<string> v;

  string tot;
  while (cin >> tot) {

    v.insert(tot);
  }

  for (auto tp : v)
    cout << tp << "\n";
  return 0;
}
