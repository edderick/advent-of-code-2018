#include <iostream>
#include <vector>
#include <locale>
#include <stack>
#include <unordered_set>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    vector<char> input;
    unordered_set<char> distinct;

    char c;
    while (cin >> c) {
        if (!input.empty() && input.back() != c && tolower(input.back()) == tolower(c)) {
            input.pop_back();
        }
        else {
            input.push_back(c);
            distinct.insert(tolower(c));
        }
    }

    size_t minSize = UINT_MAX;

    for (char c : distinct) {
        vector<char> output;

        for (char x : input) {
            if (tolower(x) == c) {
                continue;
            }
            if (!output.empty() && output.back() != x && tolower(output.back()) == tolower(x)) {
                output.pop_back();
            }
            else {
                output.push_back(x);
            }
        }
        minSize = min(minSize, output.size());
    }    

    cout << minSize << "\n";
    return 0;
}
