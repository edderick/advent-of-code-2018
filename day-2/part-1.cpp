#include <iostream> 
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[])
{

    int twoCount = 0; 
    int threeCount = 0;

    string input;
    while (cin >> input)
    {
        unordered_map<char, int> frequency;
        for (char c : input)
        {
            frequency[c]++;
        }

        for (auto f : frequency)
        {
            if (f.second == 2)
            {
                twoCount++; 
                break;
            }
        }

        for (auto f : frequency)
        {
            if (f.second == 3)
            {
                threeCount++; 
                break;
            }
        }
    }

    cout << twoCount * threeCount << "\n";

    return 0; 
}
