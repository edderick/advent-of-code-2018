#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swallow(istream& cin, int n) {
    char c; 
    for (int i = 0; i < n; i++)
        cin >> c;
}

int main(int argc, char* argv[])
{
    vector<pair<int, int>> positions;
    vector<pair<int, int>> velocities;

    long total = 0;
    string s;
    while (cin) {
        int x; int y; int dx; int dy;

        // WTF am I doing with my life?
        swallow(cin, 10);
        cin >> x;
        swallow(cin, 1);
        cin >> y;
        swallow(cin, 11);
        cin >> dx;
        swallow(cin, 1);
        cin >> dy;
        swallow(cin, 1);
        
        positions.push_back(pair<int, int>(x, y));
        velocities.push_back(pair<int, int>(dx, dy));
    }

    for (int i = 0; i < 50000; i++) {
        int minX = positions[0].first;
        int minY = positions[0].second;
        int maxX = positions[0].first;
        int maxY = positions[0].second;

        for (auto& position : positions) {
            minX = min(minX, position.first);
            minY = min(minY, position.second);
            maxX = max(maxX, position.first);
            maxY = max(maxY, position.second);
        }

        if ((maxY - minY) <= 10) {
            cout << i << "\n";

            vector<vector<char>> grid(maxY - minY + 1);
            for (auto& row : grid) {
                row.resize(maxX - minX + 1);
                for (auto& cell : row) {
                    cell = '.';
                }
            }

            for (auto& position : positions) {
                grid[position.second - minY][position.first - minX] = '#';
            }

            for (auto& row : grid) {
                for (auto& cell : row) {
                    cout << cell;
                }
                cout << "\n";
            }
        }

        for (int j = 0; j < velocities.size(); j++) {
            positions[j].first += velocities[j].first;
            positions[j].second += velocities[j].second;
        }
    }

    return 0;
}
