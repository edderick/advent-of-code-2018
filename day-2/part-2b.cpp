#include <iostream> 
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> inputs;

    string input;
    while (cin >> input)
    {
        inputs.push_back(input);
    }
    
    unordered_set<string> seen; 

    for (auto input : inputs)
    {
        for (int i = 0; i < input.size() - 1; i++)
        {
            string candidate; 
            candidate += input.substr(0, i);
            candidate += input.substr(i + 1);
            if (seen.count(candidate) == 1)
            {
                cout << candidate << "\n";
                return 0;
            }
        }
        for (int i = 0; i < input.size() - 1; i++)
        {
            string candidate; 
            candidate += input.substr(0, i);
            candidate += input.substr(i + 1);
            seen.insert(candidate);
        }
    }

    return 0; 
}
