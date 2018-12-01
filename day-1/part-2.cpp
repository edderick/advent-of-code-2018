#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    long i;
    vector<long> input;
    while (cin >> i)
    {
        input.push_back(i);
    }

    long total = 0;
    unordered_set<long> seen;
    while (true)
    {
        for (auto v : input)
        {
            if (seen.count(total) > 0)
            {
                cout << total << "\n";
                return 0;
            }
            seen.insert(total);
            total += v;
        }
    }
}
