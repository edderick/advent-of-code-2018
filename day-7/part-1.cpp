#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

int main(int argc, char* argv[])
{
    set<char> candidates;

    unordered_map<char, set<char>> before; // Before Key, value must be complete
    unordered_map<char, set<char>> after;  // After Key, value can completed

    string s;
    while (getline(cin, s)) {
        char lhs = s[36];
        char rhs = s[5];
        after[rhs].insert(lhs);
        before[lhs].insert(rhs);
    }

    for (auto c : after) {
        if (before[c.first].empty()) {
            candidates.insert(c.first);
        }
    }

    auto it = candidates.begin();
    while (!candidates.empty()) {
        cout << *it;
        for (auto c : after[*it]) {
            before[c].erase(*it);
            if (before[c].empty()) {
                candidates.insert(c);
            }
        }
        candidates.erase(it);
        it = candidates.begin();
    }

    cout << "\n";
    return 0;
}
