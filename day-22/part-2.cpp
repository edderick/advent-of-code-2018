#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>

using namespace std;

static const char ROCKY = '.';
static const char WET = '=';
static const char NARROW = '|'; 

int main(int argc, char* argv[])
{
    const int BUFFER = 500;

    long long depth;
    int targetX, targetY;
    scanf("depth: %lld ", &depth);
    scanf("target: %d,%d", &targetX, &targetY);
    cout << depth << ": " << targetX << "," << targetY << "\n";

    vector<long long> row(targetX + BUFFER, 0);
    vector<vector<long long>> geoGrid(targetY + BUFFER, row);
    vector<vector<long long>> errosionGrid(targetY + BUFFER, row);
    
    errosionGrid[0][0] = depth;

    for (int i = 1; i < targetX + BUFFER; i++)
    {
        geoGrid[0][i] = 16807 * i;
        errosionGrid[0][i] = (geoGrid[0][i] + depth) % 20183;
    }

    for (int i = 1; i < targetY + BUFFER; i++)
    {
        geoGrid[i][0] = 48271 * i;
        errosionGrid[i][0] = (geoGrid[i][0] + depth) % 20183;
    }

    for (int x = 1; x < targetX + BUFFER; x++)
    {
        for (int y = 1; y < targetY + BUFFER; y++)
        {
            if (!(x == targetX && y == targetY))
            {
                geoGrid[y][x] = errosionGrid[y - 1][x] * errosionGrid[y][x - 1];
            }
            errosionGrid[y][x] = (geoGrid[y][x] + depth) % 20183;
        }

    }

    string rowString(targetX + BUFFER, '?');
    vector<string> typeGrid(targetY + BUFFER, rowString); 

    int risk = 0; 
    for (int x = 0; x < targetX + BUFFER; x++)
    {
        for (int y = 0; y < targetY + BUFFER; y++)
        {
            const long long errosionLevel = (errosionGrid[y][x]);
            risk += errosionLevel % 3;
            switch (errosionLevel % 3)
            {
                case 0: 
                    typeGrid[y][x] = '.';
                    break; 
                case 1: 
                    typeGrid[y][x] = '=';
                    break; 
                case 2: 
                    typeGrid[y][x] = '|';
                    break;
            }
            if (false && x == targetX && y == targetY)
            {
                typeGrid[y][x] = 'T';
                break;
            }
        }
    }

    for (const string& row : typeGrid)
    {
        cout << row << "\n";
    }

    map<pair<int, int>, int> distances;
    map<pair<int, int>, int> tool;

    // 0 => Unset
    const int TORCH = 1; 
    const int GEAR = 2; 
    const int NONE = 3; 
    const int TORCH_OR_GEAR = 4;
    const int GEAR_OR_NONE = 5;
    const int TORCH_OR_NONE = 6;

    distances[pair<int,int>(0, 0)] = 0; 
    tool[pair<int, int>(0, 0)] = 1;

    deque<pair<int, int>> Q;
    Q.push_back(pair<int, int>(0, 0));
    while (!Q.empty())
    {
        const auto coord = Q.front();
        Q.pop_front();

        // North
        if (coord.second > 0)
        {
            pair<int, int> newCoord(coord.first, coord.second - 1);
            char type = typeGrid[newCoord.second][newCoord.first];
            int newTool = tool[coord]; 
            int distance = 1;
            if (type == ROCKY)
            {
                if (tool[coord] == NONE) 
                {
                    distance += 7;
                    newTool = TORCH_OR_GEAR;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = TORCH;
                }
            }
            else if (type == WET) {
                if (tool[coord] == TORCH) 
                {
                    distance += 7;
                    newTool = GEAR_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else if (type == NARROW)
            {
                if (tool[coord] == GEAR)
                {
                    distance += 7;
                    newTool = TORCH_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = TORCH;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else {
                cout << "ERROR! " << type << "\n";
            }
            if (distances.count(newCoord) == 0 || distance + distances[coord] < distances[newCoord])
            {
                tool[newCoord] = newTool;
                distances[newCoord] = distance + distances[coord]; 
                Q.push_back(newCoord);
            }
        }
        
        // East 
        if (coord.first < targetX + BUFFER - 1)
        {
            pair<int, int> newCoord(coord.first + 1, coord.second);
            char type = typeGrid[newCoord.second][newCoord.first];
            int newTool = tool[coord]; 
            int distance = 1;
            if (type == ROCKY)
            {
                if (tool[coord] == NONE) 
                {
                    distance += 7;
                    newTool = TORCH_OR_GEAR;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = TORCH;
                }
            }
            else if (type == WET) {
                if (tool[coord] == TORCH) 
                {
                    distance += 7;
                    newTool = GEAR_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else if (type == NARROW)
            {
                if (tool[coord] == GEAR)
                {
                    distance += 7;
                    newTool = TORCH_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = TORCH;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else {
                cout << "ERROR! " << type << "\n";
            }
            if (distances.count(newCoord) == 0 || distance + distances[coord] < distances[newCoord])
            {
                tool[newCoord] = newTool;
                distances[newCoord] = distance + distances[coord]; 
                Q.push_back(newCoord);
            }
        }
        
        // South
        if (coord.second < targetY + BUFFER - 1)
        {
            pair<int, int> newCoord(coord.first, coord.second + 1);
            char type = typeGrid[newCoord.second][newCoord.first];
            int newTool = tool[coord]; 
            int distance = 1;
            if (type == ROCKY)
            {
                if (tool[coord] == NONE) 
                {
                    distance += 7;
                    newTool = TORCH_OR_GEAR;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = TORCH;
                }
            }
            else if (type == WET) {
                if (tool[coord] == TORCH) 
                {
                    distance += 7;
                    newTool = GEAR_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else if (type == NARROW)
            {
                if (tool[coord] == GEAR)
                {
                    distance += 7;
                    newTool = TORCH_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = TORCH;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else {
                cout << "ERROR! " << type << "\n";
            }
            if (distances.count(newCoord) == 0 || distance + distances[coord] < distances[newCoord])
            {
                tool[newCoord] = newTool;
                distances[newCoord] = distance + distances[coord]; 
                Q.push_back(newCoord);
            }
        }
        
        // West
        if (coord.first > 0 )
        {
            pair<int, int> newCoord(coord.first - 1, coord.second);
            char type = typeGrid[newCoord.second][newCoord.first];
            int newTool = tool[coord]; 
            int distance = 1;
            if (type == ROCKY)
            {
                if (tool[coord] == NONE) 
                {
                    distance += 7;
                    newTool = TORCH_OR_GEAR;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = TORCH;
                }
            }
            else if (type == WET) {
                if (tool[coord] == TORCH) 
                {
                    distance += 7;
                    newTool = GEAR_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = GEAR;
                }
                else if (tool[coord] == TORCH_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else if (type == NARROW)
            {
                if (tool[coord] == GEAR)
                {
                    distance += 7;
                    newTool = TORCH_OR_NONE;
                }
                else if (tool[coord] == TORCH_OR_GEAR)
                {
                    newTool = TORCH;
                }
                else if (tool[coord] == GEAR_OR_NONE)
                {
                    newTool = NONE;
                }
            }
            else {
                cout << "ERROR! " << type << "\n";
            }
            if (distances.count(newCoord) == 0 || distance + distances[coord] < distances[newCoord])
            {
                tool[newCoord] = newTool;
                distances[newCoord] = distance + distances[coord]; 
                Q.push_back(newCoord);
            }
        }

    }

    for (int y = 0; y < targetY + BUFFER; y++)
    {
        for (int x = 0; x < targetX + BUFFER; x++)
        {
            cout << distances[pair<int,int>(x, y)] << " "; 
        }
        cout << "\n";
    }

    cout << distances[pair<int,int>(targetX, targetY)] << "\n";
    cout << tool[pair<int,int>(targetX, targetY)] << "\n";

    if (tool[pair<int,int>(targetX, targetY)] != 1 && 
        tool[pair<int,int>(targetX, targetY)] != 4 && 
        tool[pair<int,int>(targetX, targetY)] != 5)
    {
        cout << distances[pair<int,int>(targetX, targetY)] + 7<< "\n";
    }
    else 
    {
        cout << distances[pair<int,int>(targetX, targetY)] << "\n";
    }

    return 0;
}
