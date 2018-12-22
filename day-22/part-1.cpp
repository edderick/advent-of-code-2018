#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    int depth, targetX, targetY;
    scanf("depth: %d ", &depth);
    scanf("target: %d,%d", &targetX, &targetY);

    vector<long long> row(targetX + 1, 0);
    vector<vector<long long>> geoGrid(targetY + 1, row);
    vector<vector<long long>> errosionGrid(targetY + 1, row);
    
    errosionGrid[0][0] = depth;

    for (int i = 1; i < targetX + 1; i++)
    {
        geoGrid[0][i] = 16807 * i;
        errosionGrid[0][i] = (geoGrid[0][i] + depth) % 20183;
    }

    for (int i = 1; i < targetY + 1; i++)
    {
        geoGrid[i][0] = 48271 * i;
        errosionGrid[i][0] = (geoGrid[i][0] + depth) % 20183;
    }

    for (int x = 1; x < targetX + 1; x++)
    {
        for (int y = 1; y < targetY + 1; y++)
        {
            if (!(x == targetX && y == targetY))
            {
                geoGrid[y][x] = errosionGrid[y - 1][x] * errosionGrid[y][x - 1];
            }
            errosionGrid[y][x] = (geoGrid[y][x] + depth) % 20183;
        }

    }

    int risk = 0; 
    for (int x = 0; x < targetX + 1; x++)
    {
        for (int y = 0; y < targetY + 1; y++)
        {
            risk += errosionGrid[y][x] % 3;
        }
    }

    cout << risk << "\n";

    return 0;
}
