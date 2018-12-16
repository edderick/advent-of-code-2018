#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <cstdlib> 

using namespace std;

int main(int argc, char* argv[]) {
    string target;
    cin >> target;

    vector<int> goal;
    for (char c : target) {
        goal.push_back(atoi(&c));
    }

    vector<int> v{3, 7};

    int a = 0; 
    int b = 1;

    bool VERBOSE = false;

    while (true) {
        if (VERBOSE) {
            for (int i = 0; i < v.size(); ++i) {
                if (a == i) {
                    cout << "(" << v[i] << ")";
                }
                else if (b == i) {
                    cout << "[" << v[i] << "]";
                }
                else {
                    cout << " " << v[i] << " ";
                }
            }
            cout << "\n";
        }

        // New recipe
        int next = v[a] + v[b]; 
        if (next >= 10) {
            v.push_back(next / 10);

            bool found = false;
            for (int i = 0; i < goal.size(); i++) {
                if (v[v.size() - i - 1] != goal[goal.size() - i - 1]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "A: " << v.size() - goal.size() << "\n";
                return 0;
            }
        }
        v.push_back(next % 10);

        bool found = false;
        for (int i = 0; i < goal.size(); i++) {
            if (v[v.size() - i - 1] != goal[goal.size() - i - 1]) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "B: " << v.size() - goal.size()<< "\n";
            return 0; 
        }

        // Move elfs
        a = (1 + a + v[a]) % v.size();
        b = (1 + b + v[b]) % v.size();
    }

    return 0;
}
