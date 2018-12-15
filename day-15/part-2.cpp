#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <deque>
#include <climits>
#include <set>

using namespace std;

namespace {
static const bool VERBOSE = false;
void printGrid(const vector<string>& grid) {
    for (const string& row : grid) {
        for (const char c : row) {
            cout << c << " ";
        }
        cout << "\n";
    }
}

void printDistanceGrid(const vector<vector<int>>& distances) {
    for (const auto& row : distances) {
        for (const auto& cell : row) {
            if (cell == INT_MAX) {
                cout << ". ";
            }
            else {
                cout << cell << " ";
            }
        }
        cout << "\n";
    }
}
} // Anonymous namespace

struct EndGame {};
struct ElfDead {};

class Unit {
  public:
    enum Type {ELF, GOBLIN};

    int d_x;
    int d_y;

    Type d_type;

    int d_attackPower;
    int d_hitPoints;

    Unit(int x, int y, Type type, int attackPower = 3) 
    : d_x(x)
    , d_y(y)
    , d_type(type)
    , d_attackPower(attackPower)
    , d_hitPoints(200)
    {
    }
    
    friend ostream& operator<<(ostream& out, const Unit& unit); 

    vector<vector<int>> calculateDistances(const vector<string>& grid) const {
        vector<vector<int>> distances;
        for (const auto& row : grid) {
            vector<int> r; 
            for (const auto& cell : row) {
                r.push_back(INT_MAX);
            }
            distances.push_back(r);
        }

        // Distance, Coord (x, y)
        deque<pair<int, pair<int,int>>> q;
        q.push_back({0, {d_x, d_y}}); 
        distances[d_y][d_x] = 0; 

        set<pair<int, int>> visited;

        while (!q.empty()) {
            const auto& x = q.front();
            int dist = x.first;
            const auto coord = x.second;
            q.pop_front();
            if (coord.first < 0 || coord.first >= distances[0].size() || 
                coord.second < 0 || coord.second >= distances.size()) {
                continue; 
            }
            if (visited.count(coord) != 0) {
               continue; 
            }
            visited.insert(coord);
            if ((grid[coord.second][coord.first] == '#' || 
                 (d_type == Unit::GOBLIN && grid[coord.second][coord.first] == 'G') ||
                 (d_type == Unit::ELF && grid[coord.second][coord.first] == 'E')
                ) && 
                (d_x != coord.first || d_y != coord.second)) {
                continue;
            }
            if (dist < distances[coord.second][coord.first]) {
                distances[coord.second][coord.first] = dist;
            }

            q.push_back({dist + 1, {coord.first, coord.second - 1}});
            q.push_back({dist + 1, {coord.first, coord.second + 1}});
            q.push_back({dist + 1, {coord.first - 1, coord.second}});
            q.push_back({dist + 1, {coord.first + 1, coord.second}});
        }
        return distances;
    }

    pair<int, int> calculateNextStep(const vector<vector<int>>& distances, const Unit& target) {
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

    void attack(vector<string>& grid, const vector<vector<int>>& distances, vector<Unit>& units) {
        int minHp = INT_MAX;
        Unit *target = NULL;
        for (auto& unit : units) {
            if (d_type == unit.d_type) {
                continue;
            }

            if (distances[unit.d_y][unit.d_x] == 1) {
                if (unit.d_hitPoints > 0 && unit.d_hitPoints < minHp) {
                    target = &unit;
                    minHp = unit.d_hitPoints;
                }
                else if (unit.d_hitPoints > 0 && unit.d_hitPoints == minHp) {
                    if (unit < *target) {
                        target = &unit;
                        minHp = unit.d_hitPoints;
                    }
                }
            }
        }
        if (target) {
            target->d_hitPoints -= d_attackPower;
            if (target->d_hitPoints <= 0) {
                grid[target->d_y][target->d_x] = '.';
                if (target->d_type == Unit::ELF)
                {
                    ElfDead elfDead;
                    throw elfDead;
                }
            }
        }
    }

    void takeTurn(vector<string>& grid, vector<Unit>& units) {
        if (d_hitPoints <= 0)
        {
            throw runtime_error("I am dead.");
        }

        vector<vector<int>> distances = calculateDistances(grid); 

        int minDistance = INT_MAX;
        Unit *targetUnit = NULL;

        bool hasTarget = false; 
        for (auto& unit : units) {
            if (unit.d_type != d_type) {
                if (unit.d_hitPoints <= 0) {
                    continue;
                }
                hasTarget = true;
                if (distances[unit.d_y][unit.d_x] < minDistance) {
                    minDistance = distances[unit.d_y][unit.d_x];
                    targetUnit = &unit;
                }
                else if (distances[unit.d_y][unit.d_x] == minDistance) {
                    if (targetUnit && unit < *targetUnit) {
                        minDistance = distances[unit.d_y][unit.d_x];
                        targetUnit = &unit;
                    }
                }

            }
        }
        
        if (!hasTarget) {
            // Yes, I am using exxceptions for control flow. It came to this...
            EndGame end; 
            throw end;
        }

        if (!targetUnit) {
            return;
        }

        if (minDistance == 1) {
            attack(grid, distances, units);
        } 
        else {
            const auto p = calculateNextStep(distances, *targetUnit);

            grid[p.second][p.first] = grid[d_y][d_x];
            grid[d_y][d_x] = '.';
            d_y = p.second;
            d_x = p.first;

            if (minDistance == 2) {
                vector<vector<int>> distances = calculateDistances(grid); 
                attack(grid, distances, units);
            }
        }
    }

    bool operator<(const Unit& other) const {
        if (d_y != other.d_y) {
            return d_y < other.d_y;
        }
        else {
            return d_x < other.d_x;
        }
    }
};

ostream& operator<<(ostream& out, const Unit& unit) {
    switch (unit.d_type) {   
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

bool doesElfDie(vector<string> grid, int elfAttackPower) {
    vector<Unit> units;
    int y = 0;
    for (const string& row : grid) {
        int x = 0; 
        for (const auto& cell : row) {
            if (cell == 'E') {
                units.emplace_back(x, y, Unit::ELF, elfAttackPower);
            }
            else if (cell == 'G') {
                units.emplace_back(x, y, Unit::GOBLIN);
            }
            x++;
        }
        y++;
    }

    sort(units.begin(), units.end());

    if (VERBOSE) {
        cout << "0:\n";
        for (auto& unit : units) {
            cout << unit << "\n";
        }
        printGrid(grid);
    }

    for (int i = 1; ; i++) {
        sort(units.begin(), units.end());

        for (auto& unit : units) {
            int sum = 0; 
            for (auto& unit : units) {
                if (unit.d_hitPoints > 0) {
                    sum += unit.d_hitPoints;
                }
            }

            if (unit.d_hitPoints > 0) {
                try {
                    unit.takeTurn(grid, units);
                } 
                catch (EndGame&) {
                    cout << "STOP! " << (i - 1) << " * " << sum  << " = " <<  sum * (i - 1) << "\n";
                    return false;
                }
                catch (ElfDead) {
                    return true;
                }
            }
        }

        if (VERBOSE) {
            cout << i << ":\n";
            for (auto& unit : units) {
                if (unit.d_hitPoints > 0) {
                    cout << unit << "\n";
                }
            }
            printGrid(grid);
        }

        vector<Unit> remainers;
        for (auto& unit : units) {
            if (unit.d_hitPoints <= 0) {
                continue;
            }
            remainers.push_back(unit);
        }
        
        sort(remainers.begin(), remainers.end());
        units = remainers;
    }
}

int main(int argc, char* argv[]) {
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    // If I was a good guy, I'd try to bisect this.
    for (int i = 0; i < 50; i++)
    {
        bool wellDoesHeDieThen = doesElfDie(grid, i);
        cout << i << ": "<< (wellDoesHeDieThen ? "Elf Dead\n" : "Nope\n");
        if (!wellDoesHeDieThen)
        {
            return 0;
        }
    }
}
