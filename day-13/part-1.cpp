#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Cart
{
    Cart (int x, int y, Direction direction)
    : d_x(x), d_y(y), d_direction(direction), d_state(0)
    {
    }

    int d_x;
    int d_y;

    pair<int, int> getCoords() const
    {
        return {d_x, d_y};
    }
     
    Direction d_direction;
    int d_state;

    char getDirectionChar() const
    {
        switch (d_direction)
        {
            case Direction::UP:
                return '^';
            case Direction::DOWN:
                return 'v';
            case Direction::LEFT:
                return '<';
            case Direction::RIGHT:
                return '>';
        }
    }

    string getDirection() const
    {
        switch (d_direction)
        {
            case Direction::UP:
                return "UP";
            case Direction::DOWN:
                return "DOWN";
            case Direction::LEFT:
                return "LEFT";
            case Direction::RIGHT:
                return "RIGHT";
        }
    }

    void turnLeft()
    {
        // Rotates anti-clockwise
        switch (d_direction)
        {
            case Direction::UP:
                d_direction = Direction::LEFT;
                break;
            case Direction::LEFT:
                d_direction = Direction::DOWN;
                break;
            case Direction::DOWN:
                d_direction = Direction::RIGHT;
                break;
            case Direction::RIGHT:
                d_direction = Direction::UP;
                break;
        }
    }

    void turnRight()
    {
        // Rotates clockwise
        switch (d_direction)
        {
            case Direction::UP:
                d_direction = Direction::RIGHT;
                break;
            case Direction::RIGHT:
                d_direction = Direction::DOWN;
                break;
            case Direction::DOWN:
                d_direction = Direction::LEFT;
                break;
            case Direction::LEFT:
                d_direction = Direction::UP;
                break;
        }
    }

    void move(const vector<string>& grid)
    {
        switch (d_direction)
        {
            case Direction::UP:
                d_y--;
                break;
            case Direction::DOWN:
                d_y++;
                break;
            case Direction::LEFT:
                d_x--;
                break;
            case Direction::RIGHT:
                d_x++;
                break;
        }
        
        const char cell = grid[d_y][d_x];

        if (cell == '\\')
        {
            switch (d_direction)
            {
                case Direction::UP:
                    d_direction = Direction::LEFT;
                    break;
                case Direction::DOWN:
                    d_direction = Direction::RIGHT;
                    break;
                case Direction::LEFT:
                    d_direction = Direction::UP;
                    break;
                case Direction::RIGHT:
                    d_direction = Direction::DOWN;
                    break;
            }
        }
        else if (cell == '/')
        {
            switch (d_direction)
            {
                case Direction::UP:
                    d_direction = Direction::RIGHT;
                    break;
                case Direction::DOWN:
                    d_direction = Direction::LEFT;
                    break;
                case Direction::LEFT:
                    d_direction = Direction::DOWN;
                    break;
                case Direction::RIGHT:
                    d_direction = Direction::UP;
                    break;
            }
        }
        else if (cell == '+')
        {
            if (d_state == 0)
            {
                turnLeft();
            }
            else if (d_state == 1)
            {
                // NO-OP
            }
            else if (d_state == 2)
            {
                turnRight();
            }

            d_state = (d_state + 1) % 3;
        }
    }

    bool operator <(const Cart& other) const
	{
		if (d_y < other.d_y)
        {
            return true;
        }
        return d_x < other.d_x;
	}
};

ostream& operator<< (ostream &output, Cart cart)
{
    output << "(" << cart.d_x << "," << cart.d_y << ") " << cart.getDirection() << ":" << cart.d_state; 
    return output;
}

void printGrid(const vector<string>& grid)
{
    for (auto row : grid)
    {
        cout << row << "\n";
    }
}

void printCarts(const vector<Cart>& carts)
{
    for (auto cart : carts)
    {
        cout << cart << "\n";
    }
}

void printBanner(int width)
{
    cout << "\n";
    for (int i = 0; i < width; i++)
    {
        cout << "*";
    }
    cout << "\n";
    cout << "\n";
}

int main(int argc, char* argv[])
{   
    bool VERBOSE = false;

    vector<string> grid;
    vector<Cart> carts;

    int y = 0; 
    string line;
    while (getline(cin, line))
    {
        int x = 0;
        string row;
        for (char c : line)
        {
            switch (c)
            {
                case '-': case '|': case '+': case '\\': case '/': case ' ':
                    row += c;
                    break; 
                case '>':
                    carts.emplace_back(x, y, Direction::RIGHT);
                    row += '-';
                    break;
                case '<':
                    carts.emplace_back(x, y, Direction::LEFT);
                    row += '-';
                    break;
                case '^':
                    carts.emplace_back(x, y, Direction::UP);
                    row += '|';
                    break;
                case 'v':
                    carts.emplace_back(x, y, Direction::DOWN);
                    row += '|';
                    break;
            }
            x++;
        }
        grid.push_back(row);
        y++;
    }

    if (VERBOSE)
    {
        printGrid(grid);
        printCarts(carts);
        printBanner(80);
    }

    for (; ;)
    {
        sort(carts.begin(), carts.end());
        vector<string> currentGrid = grid;
        for (auto& cart: carts)
        {
            currentGrid[cart.d_y][cart.d_x] = cart.getDirectionChar(); 
        }

        if (VERBOSE) 
        {
            printGrid(currentGrid);
            printCarts(carts);
            printBanner(80);
        }

        for (auto& cart : carts)
        {
            cart.move(grid);

            set<pair<int, int>> set;
            for (const auto& cart : carts)
            {
                bool crash = false;
                if (set.count(cart.getCoords()) != 0)
                {
                    cout << cart << "\n";
                    crash = true;
                }
                else {
                    set.insert(cart.getCoords());
                }
                if (crash)
                {
                    return 0; 
                }
            }
        }
    }

    return 0;
}
