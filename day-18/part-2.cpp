#include <iostream>
#include <vector>
#include <map>

using namespace std;

void printGrid(const vector<string>& grid)
{
    for (const auto& row : grid)
    {
        cout << row << "\n";
    }
    cout << "\n";
}

int countAdjacent(int x, int y, char c, const vector<string>& grid)
{
    const int width = grid[0].size();
    const int height = grid.size();

    int count = 0;
    // E SE S SW W

    // N
    if (y > 0 && grid[y - 1][x] == c)
    {
        count++;
    }

    // NE 
    if (y > 0 && x + 1 < width && grid[y - 1][x + 1] == c)
    {
        count++;
    }

    // E 
    if (x < width && grid[y][x + 1] == c)
    {
        count++;
    }

    // SE 
    if (y + 1 < width && x + 1< width && grid[y + 1][x + 1] == c)
    {
        count++;
    }

    // S
    if (y + 1 < width && grid[y + 1][x] == c)
    {
        count++;
    }

    // SW
    if (y + 1 < width && x > 0 && grid[y + 1][x - 1] == c)
    {
        count++;
    }

    // W
    if (x > 0 && grid[y][x - 1] == c)
    {
        count++;
    }

    // NW
    if (x > 0 && y > 0 && grid[y - 1][x - 1] == c)
    {
        count++;
    }
    return count;
}

int main(int argc, char* argv[])
{
    vector<string> grid;
    string line;
    while (getline(cin, line))
    {
        grid.push_back(line);
    }

    const int width = grid[0].size();
    const int height = grid.size();

    vector<vector<string>> grids;
    map<vector<string>, int> seen;
    seen[grid] = 0;

    printGrid(grid);

    const long MAX = 1000000000;

    long start = 0; 
    long end = 0; 

    for (long i = 0; i < 1000000000; i++)
    {
        auto newGrid = grid;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                const auto& cell = grid[y][x];
                if (cell == '.')
                {
                    if (countAdjacent(x, y, '|', grid) >= 3)
                    {
                        newGrid[y][x] = '|';
                    }
                }
                else if (cell == '|') 
                {
                    if (countAdjacent(x, y, '#', grid) >= 3)
                    {
                        newGrid[y][x] = '#';
                    }
                }
                else if (cell == '#')
                {
                    if (countAdjacent(x, y, '#', grid) >= 1 && countAdjacent(x, y, '|', grid) >= 1)
                    {
                        newGrid[y][x] = '#';
                    }
                    else 
                    {
                        newGrid[y][x] = '.';
                    }
                }
            }
        }
    
        auto it = seen.find(newGrid);
        if (it != seen.end())
        {
            cout << i << " : " << it->second << "\n";
            start = it->second; 
            end = i;
            break;
        }
        seen[newGrid] = i; 
        grids.push_back(newGrid);

        grid = newGrid;
        printGrid(grid);
    }

    long num = (MAX - 1 - end) % (end - start) + start;
    cout << "Num: " << num << "\n"; 

    int trees = 0;
    int lumberyards = 0; 
    for (const auto& row : grids[num])
    {
        for (const auto& cell : row)
        {
            if (cell == '|')
            {
                trees++; 
            }
            else if (cell == '#')
            {
                lumberyards++; 
            }
        }
    }

    cout << "Lumberyards: " << lumberyards << "\n";
    cout << "Trees: " << trees << "\n";
    cout << "Total: " << lumberyards * trees << "\n";

    return 0;
}
