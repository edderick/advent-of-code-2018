#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <deque>
#include <climits>
#include <set>

using namespace std;

void printGrid(const vector<string>& grid)
{
    for (const string& row : grid)
    {
        for (const char c : row)
        {
            cout << c << " ";
        }
        cout << "\n";
    }
}

void printDistanceGrid(const vector<vector<int>>& distances)
{
    for (const auto& row : distances)
    {
        for (const auto& cell : row)
        {
            if (cell == INT_MAX)
            {
                cout << ". ";
            }
            else {
                cout << cell << " ";
            }
        }
        cout << "\n";
    }
}

class Unit {
  public:
    enum Type {ELF, GOBLIN};

    int d_x;
    int d_y;

    Type d_type;

    int d_attackPower;
    int d_hitPoints;

    Unit(int x, int y, Type type) 
    : d_x(x)
    , d_y(y)
    , d_type(type)
    , d_attackPower(3)
    , d_hitPoints(200)
    {
    }
    
    friend ostream& operator<<(ostream& out, const Unit& unit); 

    vector<vector<int>> calculateDistances(const vector<string>& grid) const
    {
        // Hi, I'm not sure if this is going to be efficient enough, but it's
        // probably close enough!
        vector<vector<int>> distances;
        for (const auto& row : grid)
        {
            vector<int> r; 
            for (const auto& cell : row)
            {
                r.push_back(INT_MAX);
            }
            distances.push_back(r);
        }

        // Distance, Coord (x, y)
        deque<pair<int, pair<int,int>>> q;
        q.push_back({0, {d_x, d_y}}); 
        distances[d_y][d_x] = 0; 

        set<pair<int, int>> visited;

        while (!q.empty())
        {
            const auto& x = q.front();
            int dist = x.first;
            const auto coord = x.second;
            q.pop_front();
            if (coord.first < 0 || coord.first >= distances[0].size() || 
                coord.second < 0 || coord.second >= distances.size())
            {
                continue; 
            }
            if (visited.count(coord) != 0)
            {
               continue; 
            }
            visited.insert(coord);
            if ((grid[coord.second][coord.first] == '#' || 
                 (d_type == Unit::GOBLIN && grid[coord.second][coord.first] == 'G') ||
                 (d_type == Unit::ELF && grid[coord.second][coord.first] == 'E')
                ) && 
                (d_x != coord.first || d_y != coord.second))
            {
                continue;
            }
            if (dist < distances[coord.second][coord.first])
            {
                distances[coord.second][coord.first] = dist;
            }

            q.push_back({dist + 1, {coord.first, coord.second - 1}});
            q.push_back({dist + 1, {coord.first, coord.second + 1}});
            q.push_back({dist + 1, {coord.first - 1, coord.second}});
            q.push_back({dist + 1, {coord.first + 1, coord.second}});
        }
        return distances;
    }

    pair<int, int> calculateNextStep(const vector<vector<int>>& distances, const Unit& target)
    {
        pair<int,int> t(target.d_x, target.d_y);

        while (distances[t.second][t.first] != 1) {
            if (distances[t.second - 1][t.first] == distances[t.second][t.first] - 1) {
                t.second--;
            }
            else if (distances[t.second][t.first - 1] == distances[t.second][t.first] - 1) {
                t.first--;
            }
            else if (distances[t.second][t.first + 1] == distances[t.second][t.first] - 1) {
                t.first++;
            }
            else if (distances[t.second + 1][t.first] == distances[t.second][t.first] - 1) {
                t.second++;
            }
        }
            
        return t;
    }

    void attack(vector<string>& grid, const vector<vector<int>>& distances, vector<Unit>& units)
    {
        int minHp = INT_MAX;
        Unit *target = NULL;
        for (auto& unit : units)
        {
            if (d_type == unit.d_type)
            {
                continue;
            }

            if (distances[unit.d_y][unit.d_x] == 1)
            {
                if (unit.d_hitPoints > 0 && unit.d_hitPoints < minHp)
                {
                    target = &unit;
                    minHp = unit.d_hitPoints;
                }
                else if (unit.d_hitPoints > 0 && unit.d_hitPoints == minHp)
                {
                    if (unit < *target)
                    {
                        target = &unit;
                        minHp = unit.d_hitPoints;
                    }
                }
            }
        }
        if (target)
        {
            //cout << *this << " attacked: " << *target << "\n";
            target->d_hitPoints -= d_attackPower;
            if (target->d_hitPoints <= 0)
            {
                grid[target->d_y][target->d_x] = '.';
            }
        }
    }

    void takeTurn(vector<string>& grid, vector<Unit>& units)
    {
        // each unit that is still alive takes a turn
        if (d_hitPoints <= 0)
        {
            throw runtime_error("I am dead.");
        }

        // Find target
        vector<vector<int>> distances = calculateDistances(grid); 
        //printDistanceGrid(distances);

        int minDistance = INT_MAX;
        Unit *targetUnit = NULL;

        bool hasTarget = false; 
        for (auto& unit : units)
        {
            if (unit.d_type != d_type)
            {
                if (unit.d_hitPoints <= 0)
                {
                    continue;
                }
                hasTarget = true;
                if (distances[unit.d_y][unit.d_x] < minDistance)
                {
                    minDistance = distances[unit.d_y][unit.d_x];
                    targetUnit = &unit;
                }
                else if (distances[unit.d_y][unit.d_x] == minDistance)
                {
                    if (targetUnit && unit < *targetUnit)
                    {
                        minDistance = distances[unit.d_y][unit.d_x];
                        targetUnit = &unit;
                    }
                }

            }
        }
        
        if (!hasTarget)
        {
            throw 1;
        }

        if (!targetUnit)
        {
            return; // No-one to target :(
        }
        //cout << *this << " is targeting: " << *targetUnit << "\n";

        if (minDistance == 1) // Can attack
        {
            //cout << "ATTACK!\n";  
            attack(grid, distances, units);
        } 
        else 
        {
            const auto p = calculateNextStep(distances, *targetUnit);

            grid[p.second][p.first] = grid[d_y][d_x];
            grid[d_y][d_x] = '.';
            d_y = p.second;
            d_x = p.first;

            if (minDistance == 2)
            {
                //cout << "ATTACK! (after moved)\n"; 
                //TODO: Optimize
                vector<vector<int>> distances = calculateDistances(grid); 
                attack(grid, distances, units);
            }
        }

    }

    bool operator<(const Unit& other) const
    {
        if (d_y != other.d_y)
        {
            return d_y < other.d_y;
        }
        else 
        {
            return d_x < other.d_x;
        }
    }

};

ostream& operator<<(ostream& out, const Unit& unit) 
{
    switch (unit.d_type)
    {   
        case Unit::ELF:
            out << "E";
            break;
        case Unit::GOBLIN:
            out << "G";
            break;
    }
    out << "(" << unit.d_x << "," << unit.d_y << ") [" << unit.d_hitPoints << "]";
    return out;
}


int main(int argc, char* argv[])
{
    vector<string> grid;
    string line;
    while (getline(cin, line))
    {
        grid.push_back(line);
    }

    vector<Unit> units;
    int y = 0;
    for (const string& row : grid)
    {
        int x = 0; 
        for (const auto& cell : row)
        {
            if (cell == 'E')
            {
                units.emplace_back(x, y, Unit::ELF);
            }
            else if (cell == 'G')
            {
                units.emplace_back(x, y, Unit::GOBLIN);
            }
            x++;
        }
        y++;
    }

    sort(units.begin(), units.end());

    for (auto& unit : units)
    {
        //cout << unit << "\n";
    }
    //printGrid(grid);

    for (int i = 1; i < 300; i++)
    {
        sort(units.begin(), units.end());

        for (auto& unit : units)
        {
            bool hasElf = false;
            bool hasGoblin = false;
            int sum = 0; 
            for (auto& unit : units)
            {
                if (unit.d_hitPoints <= 0)
                {
                    continue;
                }
                sum += unit.d_hitPoints;
                if (unit.d_type == Unit::GOBLIN)
                {
                    hasGoblin = true;
                }
                else if (unit.d_type == Unit::ELF)
                {
                    hasElf = true;
                }
            }
            //if (!hasElf || !hasGoblin)
            //{
            //    printGrid(grid);
            //    cout << "STOP! " << (i - 1) << " * " << sum  << " = " <<  sum * (i - 1) << "\n";
            //    return 0;
            //}

            if (unit.d_hitPoints > 0)
            {
                try {
                    unit.takeTurn(grid, units);
                } catch(...) {
                    cout << "STOP! " << (i - 1) << " * " << sum  << " = " <<  sum * (i - 1) << "\n";
                    return 0;
                }
            }
        }
        for (auto& unit : units)
        {
            //cout << unit << "\n";
        }
        vector<Unit> remainers;
        for (auto& unit : units)
        {
            if (unit.d_hitPoints <= 0)
            {
                continue;
            }
            remainers.push_back(unit);
        }
        
        sort(remainers.begin(), remainers.end());

#if 0
        bool hasElf = false;
        bool hasGoblin = false;
        int sum = 0; 
        cout << i << ":\n";
        for (auto& unit : remainers)
        {
            //cout << unit << "\n";
            sum += unit.d_hitPoints;
            if (unit.d_type == Unit::GOBLIN)
            {
                hasGoblin = true;
            }
            else if (unit.d_type == Unit::ELF)
            {
                hasElf = true;
            }
        }
        printGrid(grid);
        if (!hasElf || !hasGoblin)
        {
            cout << "DONE! " << i << " * " << sum  << " = " <<  sum * i << "\n";
            return 0;
        }
        cout << "\n";
#endif
        units = remainers;

    }

    return 0;
}
