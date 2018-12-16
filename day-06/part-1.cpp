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
    int width = maxX - minX + 5;
    int height = maxY - minY + 5;

    // Row, Col : coords[i], minDistance
    vector<vector<pair<int, int>>> grid(height);
    for (auto& row : grid)
    {
        row.resize(width);
        for (auto& cell : row)
        {
            cell.second = INT_MAX;
        }
    }

    int i = 0;
    for (const auto c : coords)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int distance = abs(x - c.first) + abs(y - c.second); 
                if (distance < grid[y][x].second)
                {
                    grid[y][x].first = i;
                    grid[y][x].second = distance;
                }
                else if (distance == grid[y][x].second)
                {
                    if (x == 0 && y == 0)
                    {
                        cout << c.first << "\n";
                    }
                    grid[y][x].first = -1; // Multiple
                }
            }
        }
        i++; // TODO:
    }

    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            if (cell.first == -1)
            { 
                cout << ". ";
            }
            else {
                cout << cell.first << " "; 
            }
        }
        cout << "\n";
    }

    unordered_set<int> infinite;
    for (int y = 0; y < height; y++)
    {
        infinite.insert(grid[y][0].first);
        infinite.insert(grid[y][width - 1].first);
    }
    for (int x = 0; x < width; x++)
    {
        infinite.insert(grid[0][x].first);
        infinite.insert(grid[height - 1][x].first);
    }
    
    cout << infinite.size() << "\n";

    unordered_map<int, int> counter;
    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            if (infinite.count(cell.first) == 0 && cell.first != -1)
            {
                counter[cell.first]++;
            }
        }
    }
    
    int maxVal = 0;
    int maxIndex = 0;
    for (const auto c : counter)
    {
        if (c.second > maxVal)
        {
            maxVal = c.second;
            maxIndex = c.first;
        }
    }

    cout << maxIndex << ": " << maxVal << "\n";

    return 0;
}
