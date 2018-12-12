#include <iostream>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {
    string input; 
    getline(cin, input);
    const string initialState = input.substr(15);

    getline(cin, input);

    unordered_map<string, char> map; 
    while (getline(cin, input)) {
        map[input.substr(0,5)] = input.substr(9)[0];
    }

    string oldState = ".........." + initialState + "..........";
    string newState;

    // Seems to stabilize after 200...
    for (int x = 0; x < 200; x++) {
        newState = "..";
        for (int i = 2; i < oldState.size() ; i++) {
            if (map.count(oldState.substr(i - 2, 5)) == 0) {
                newState += '.';
            }
            else {
                newState += map[oldState.substr(i - 2, 5)]; 
            }
        }
        oldState = newState + ".";
        newState = "";
    }

    long long total = 0;
    long long i = -10 + 50'000'000'000 - 200;
    for (auto& c : oldState) {
        if (c == '#') {
            total += i;
        }
        i++;
    }
    cout << total << "\n";
    return 0;
}
