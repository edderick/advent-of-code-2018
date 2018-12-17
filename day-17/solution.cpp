#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Row {
  public:
    char d_first; 
    char d_second;

    int d_firstPos;
    int d_secondStart; 
    int d_secondEnd;

  public: 
    Row(char first, char second, int firstPos, int secondStart, int secondEnd)
    : d_first(first) 
    , d_second(second)
    , d_firstPos(firstPos)
    , d_secondStart(secondStart)
    , d_secondEnd(secondEnd)
    {
    }
};

void printGrid(const vector<string>& grid, int minX, int maxX)
{
    for (const string& row : grid)
    {
        for (int i = minX - 1; i <= maxX + 1; i++)
        {
            cout << row[i];
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[])
{
    int minY = INT_MAX;
    int maxY = 0; 
    int minX = INT_MAX;
    int maxX = 0;

    char first, second; 
    int first_pos, second_start, second_end;

    vector<Row> rows;

    while (scanf("%c=%d, %c=%d..%d\n", &first, &first_pos, &second, &second_start, &second_end) > 0)
    {
        rows.emplace_back(first, second, first_pos, second_start, second_end);;
        if (first == 'x')
        {
            minX = min(minX, first_pos);
            maxX = max(maxX, first_pos);
            minY = min(minY, second_start);
            maxY = max(maxY, second_end);
        }
        else 
        {
            minY = min(minY, first_pos);
            maxY = max(maxY, first_pos);
            minX = min(minX, second_start);
            maxX = max(maxX, second_end);
        }
    }

    cout << "minY: " << minY << "\n";
    cout << "maxY: " << maxY << "\n";
    cout << "minX: " << minX << "\n";
    cout << "maxX: " << maxX << "\n";

    string s(maxX + 2, '.');
    vector<string> grid(maxY + 1, s);
    grid[0][500] = '+';
    grid[1][500] = '|';
    
    for (const auto& row : rows)
    {
        for (int i = row.d_secondStart; i <= row.d_secondEnd; i++)
        {
            if (row.d_first == 'x')
            {
                grid[i][row.d_firstPos] = '#';
            }
            else 
            {
                grid[row.d_firstPos][i] = '#';
            }
        }
    }

    // Could find a better termination condition, but this is fine for my input
    for (int a = 0; a < 1000; a++)
    {
        for (int i = 0; i < maxY; i++)
        {
            for (int j = minX - 1; j < maxX + 2; j++)
            {
                // XXX: This should be refactored, but it's quarter to midnight.
                if (grid[i][j] == '|')
                {
                    if (grid[i + 1][j] == '|')
                    {
                        continue;
                    }
                    else if (grid[i + 1][j] == '.')
                    {
                        grid[i + 1][j] = '|';
                    }
                    else if (grid[i + 1][j] == '#')
                    {
                        bool enclosed = true;
                        {
                            int left = 0;
                            while (grid[i][j - left] != '#')
                            {
                                if (grid[i + 1][j - left] == '.' || grid[i + 1][j - left] == '|')
                                {
                                    enclosed = false;
                                    break;
                                }
                                else {
                                    left++;
                                }
                            }
                            int right = 0;
                            while (grid[i][j + right] != '#')
                            {
                                if (grid[i + 1][j + right] == '.' || grid[i + 1][j + right] == '|')
                                {
                                    enclosed = false;
                                    break;
                                }
                                else {
                                    right++;
                                }
                            }
                        }

                        if (enclosed)
                        {
                            int left = 0;
                            while (grid[i][j - left] != '#')
                            {
                                if (grid[i + 1][j - left] == '.' || grid[i + 1][j - left] == '|')
                                {
                                    grid[i][j - left] = '|';
                                    break;
                                }
                                grid[i][j - left] = '~';
                                left++; 
                            }
                            int right = 0;
                            while (grid[i][j + right] != '#' || grid[i + 1][j + right] == '|')
                            {
                                if (grid[i + 1][j + right] == '.')
                                {
                                    grid[i][j + right] = '|';
                                    break;
                                }
                                grid[i][j + right] = '~';
                                right++; 
                            }
                        }
                        else 
                        {
                            int left = 0;
                            while (grid[i][j - left] != '#')
                            {
                                if (grid[i + 1][j - left] != '.' && grid[i + 1][j - left] != '|')
                                {
                                    grid[i][j - left] = '|';
                                    left++; 
                                }
                                else {
                                    grid[i][j - left] = '|';
                                    break; 
                                }
                            }
                            int right = 0;
                            while (grid[i][j + right] != '#')
                            {
                                if (grid[i + 1][j + right] != '.' && grid[i + 1][j + right] != '|')
                                {
                                    grid[i][j + right] = '|';
                                    right++; 
                                }
                                else {
                                    grid[i][j + right] = '|';
                                    break; 
                                }
                            }
                        }
                    }
                    else if (grid[i + 1][j] == '~')
                    {
                        bool enclosed = true;
                        {
                            int left = 0;
                            while (grid[i][j - left] != '#')
                            {
                                if (grid[i + 1][j - left] == '.' || grid[i + 1][j - left] == '|')
                                {
                                    enclosed = false;
                                    break;
                                }
                                else {
                                    left++;
                                }
                            }
                            int right = 0;
                            while (grid[i][j + right] != '#')
                            {
                                if (grid[i + 1][j + right] == '.' || grid[i + 1][j + right] == '|')
                                {
                                    enclosed = false;
                                    break;
                                }
                                else {
                                    right++;
                                }
                            }
                        }

                        if (enclosed)
                        {
                            int left = 0;
                            while (grid[i][j - left] != '#')
                            {
                                if (grid[i + 1][j - left] != '.')
                                {
                                    grid[i][j - left] = '~';
                                    left++; 
                                }
                                else {
                                    grid[i][j - left] = '|';
                                    break; 
                                }
                            }
                            int right = 0;
                            while (grid[i][j + right] != '#')
                            {
                                if (grid[i + 1][j + right] != '.')
                                {
                                    grid[i][j + right] = '~';
                                    right++; 
                                }
                                else {
                                    grid[i][j + right] = '|';
                                    break; 
                                }
                            }
                        }
                        else 
                        {
                            int left = 0;
                            while (grid[i][j - left] != '#')
                            {
                                if (grid[i + 1][j - left] != '.' && grid[i + 1][j - left] != '|')
                                {
                                    grid[i][j - left] = '|';
                                    left++; 
                                }
                                else {
                                    grid[i][j - left] = '|';
                                    break; 
                                }
                            }
                            int right = 0;
                            while (grid[i][j + right] != '#')
                            {
                                if (grid[i + 1][j + right] != '.' && grid[i + 1][j + right] != '|')
                                {
                                    grid[i][j + right] = '|';
                                    right++; 
                                }
                                else {
                                    grid[i][j + right] = '|';
                                    break; 
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printGrid(grid, minX, maxX);
    cout << "\n";

    int partOneSum = 0; 
    int partTwoSum = 0; 
    int y = 0; 
    for (int i = 0; i < grid.size(); i++)
    {
        if (i < minY)
        {
            continue;
        }
        for (const char c : grid[i])
        {
            if (c == '~')
            {
                partOneSum++;
                partTwoSum++;
            }
            else if (c == '|')
            {
                partOneSum++;
            }
        }
    }

    cout << "Part 1 Sum: " << partOneSum << "\n";
    cout << "Part 2 Sum: " << partTwoSum << "\n";

    return 0;
}
