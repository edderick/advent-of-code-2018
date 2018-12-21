#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string input;
    cin >> input;
    input = input.substr(1, input.size() - 2);

    map<pair<int, int>, int> distances;
    distances[pair<int,int>(0,0)] = 0;

    stack<pair<int, int>> positions;
    pair<int, int> position; 

    for (const char c : input) {
        const pair<int, int> old_position = position; 

        switch (c) {
            case '(':
                positions.push(position);
                break;
            case '|': 
                position = positions.top();
                break; 
            case ')':
                position = positions.top();
                positions.pop();
                break; 
            case 'N':
                position.second -= 1;
                break; 
            case 'E':
                position.first += 1; 
                break;
            case 'S':
                position.second += 1;
                break;
            case 'W':
                position.first -= 1; 
                break;
        }
        
        if (distances.count(position) == 0) {
            distances[position] = distances[old_position] + 1;
        }
        else if (distances[position] > distances[old_position] + 1) {
            distances[position] = distances[old_position] + 1;
        }
    }

    int maxDistance = 0;
    for (auto d : distances) {
        if (d.second > maxDistance) {
            maxDistance = d.second;
        }
    }
    cout << "Part 1: "<< maxDistance << "\n";

    int count = 0;
    for (auto d : distances) {
        if (d.second >= 1000) {
            count++;
        }
    }
    cout << "Part 2: " << count << "\n";

    return 0;
}
