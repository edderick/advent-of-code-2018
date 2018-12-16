#include <iostream>
#include <vector>
#include <locale>

using namespace std;

int main(int argc, char* argv[]) {
    vector<char> output;

    char c;
    while (cin >> c) {
        if (!output.empty() && output.back() != c && tolower(output.back()) == tolower(c)) {
            output.pop_back();
        }
        else {
            output.push_back(c);
        }
    }
        
    cout << output.size() << "\n";
    return 0;
}
