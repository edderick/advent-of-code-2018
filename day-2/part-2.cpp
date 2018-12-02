#include <iostream> 
#include <unordered_map>
#include <vector>

using namespace std;

int numDifferences(const string& lhs, const string& rhs)
{
    int count = 0;
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs[i] != rhs[i])
        {
            count++;
        }
    }
    return count;
}

void printDifderences(const string& lhs, const string& rhs)
{
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs[i] == rhs[i])
        {
            cout << lhs[i];
        }
    }
    cout << "\n";
}

int main(int argc, char* argv[])
{
    vector<string> inputs;

    string input;
    while (cin >> input)
    {
        inputs.push_back(input);
    }
    
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        for (size_t j = i + 1; j < inputs.size(); ++j)
        {
            if (numDifferences(inputs[i], inputs[j]) == 1)
            {
                printDifderences(inputs[i], inputs[j]);
                return 0;
            }
        }
    }

    return 0; 
}
