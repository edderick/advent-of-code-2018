#include <iostream>
#include <vector> 

using namespace std;

int main(int argc, char* argv[]) {
    long target;
    cin >> target;

    vector<int> v{3, 7};

    int a = 0; 
    int b = 1;

    vector<int> result;

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
            v.push_back(next / 10 );
            if (v.size() > target) {
                result.push_back(next / 10);
                if (result.size() >= 10) {
                    break;
                }
            }
        }
        v.push_back(next % 10);
        if (v.size() > target) {
            result.push_back(next % 10);
            if (result.size() >= 10) {
                break;
            }
        }

        // Move elfs
        a = (1 + a + v[a]) % v.size();
        b = (1 + b + v[b]) % v.size();
    }

    for (int i : result) {
        cout << i;
    }
    cout << "\n";

    return 0;
}
