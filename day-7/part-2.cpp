#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

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

    int NUM_WORKERS = 5;
    int CONSTANT_TIME = 60;

    vector<pair<char, int>> workers;
    for (int i = 0; i < NUM_WORKERS; i++) {
        workers.push_back(pair<char, int>('-', 0));
    }

    int i = 0; 
    while (true) {
        for (auto& w : workers) {
            if (w.second <= 0) {
                if (w.first != '-') {
                    for (auto c : after[w.first]) {
                        before[c].erase(w.first);
                        if (before[c].empty()) {
                            candidates.insert(c);
                        }
                    }
                }
            }
        }
        for (auto& w : workers) {
            if (w.second <= 0) {
                if (!candidates.empty()) {
                    w.first = *candidates.begin();
                    w.second = CONSTANT_TIME + (w.first - 'A' + 1);
                    candidates.erase(w.first);
                }
                else {
                    w.first = '-';
                    w.second = 0; 
                }
            }
            if (w.first != '-') {
                w.second = w.second - 1;
            }
        }

        if (candidates.empty()) {
            bool hasActiveJobs = false;
            for (auto w : workers) {
                if (w.first != '-') {
                    hasActiveJobs = true;
                }
            }
            if (!hasActiveJobs) {
                cout << i << "\n"; 
                return 0;
            }
        }

        i++;
    }
}
