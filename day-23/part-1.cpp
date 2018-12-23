#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct NanoBot
{
    NanoBot() 
    : d_id(rand())
    {
    }

    int d_id;

    int d_x; 
    int d_y; 
    int d_z;
    int d_r;

    friend ostream& operator<<(ostream& stream, const NanoBot& nanobot);

    bool inRange(const NanoBot& other)
    {
        int distance = abs(d_x - other.d_x) + abs(d_y - other.d_y) + abs(d_z - other.d_z);
        return distance <= d_r;
    }

    bool operator==(const NanoBot& other) const
    {
        return d_id == other.d_id;
    }
};

ostream& operator<<(ostream& stream, const NanoBot& nanobot)
{
    stream << "(" << nanobot.d_x << ", "<< nanobot.d_y << ", "<< nanobot.d_z 
            << ") [" << nanobot.d_r << "]";
    return stream; 
}

int main(int argc, char* argv[])
{
    vector<NanoBot> bots;
    while (true)
    {
        NanoBot n; 
        scanf("pos=<%d,%d,%d>, r=%d", &n.d_x, &n.d_y, &n.d_z, &n.d_r);
        bots.push_back(n);
        if (getchar() == EOF)
        {
            break; // I can't read input today :(
        }
    }

    NanoBot bestBot = bots[0];
    for (const auto& bot : bots)
    {
        if (bot.d_r > bestBot.d_r)
        {
            bestBot = bot;
        }
    }

    int count = 0; 
    cout << bestBot << "\n";
    for (const auto& bot : bots)
    {
        cout << bot;
        if (bestBot.inRange(bot))
        {
            cout << " in range\n";
            count++;
        }
        else
        {
            cout << " not in range\n";
        }
    }

    cout << "Num in range: " << count << "\n"; 

    return 0;
}
