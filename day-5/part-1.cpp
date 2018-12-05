#include <iostream>
#include <vector>
#include <locale>
#include <stack>

using namespace std;

int main(int argc, char* argv[])
{
    vector<char> input;
    char c;
    while (cin >> c)
    {
        input.push_back(c);
    }

    int count = 0; 


    stack<char> lookBack; 
    lookBack.push(input[0]);

    for (int i = 1; i < input.size(); i++)
    {
        if (lookBack.empty())
        {
            lookBack.push(input[i]);
            continue;
        }

        if (lookBack.top() != input[i] && tolower(lookBack.top()) == tolower(input[i]))
        {
            lookBack.pop();
            count++;
        }
        else 
        {
            lookBack.push(input[i]);
        }
    }
        
    cout << input.size() - (2 * count) << "\n";

    return 0;
}
