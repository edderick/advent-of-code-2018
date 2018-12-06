#include <iostream>
#include <vector> 
#include <utility>
#include <numeric>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[])
{
    vector<pair<int, int>> coords;

    int x;
    int y;
    char c;
    while (cin >> x)
    {
        cin >> c >> y;
        coords.push_back(pair<int,int>(x,y));
    }

    int minX = INT_MAX;
    int maxX = 0;
    int minY = INT_MAX;
    int maxY = 0;
        
    for (auto c : coords)
    {
        minX = min(minX, c.first);
        maxX = max(maxX, c.first);
        minY = min(minY, c.second);
        maxY = max(maxY, c.second);
    }

    // TODO: Firgure out the right thing here
    int width = maxX - minX + 200;
    int height = maxY - minY + 200;

    // Row, Col : coords[i], minDistance
    vector<vector<int>> grid(height);
    for (auto& row : grid)
    {
        row.resize(width);
        for (auto& cell : row)
        {
            cell = 0;
        }
    }

    for (int y = -100; y < height - 100; y++)
    {
        for (int x = -100; x < width - 100; x++)
        {
            int total = 0; 
            for (const auto c : coords)
            {
                int distance = abs(x - c.first) + abs(y - c.second); 
                total += distance; 
            }
            grid[y + 100][x + 100] = total;
        }
    }

    int count = 0;
    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            if (cell < 10000)
            {
                count++;
            }
        }
    }
    
    cout << count << "\n";

    return 0;
}
