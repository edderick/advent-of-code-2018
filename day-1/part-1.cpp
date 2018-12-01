#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    long total = 0;
    long i;
    while (cin >> i)
    {
        total += i;
    }
    cout << total << "\n";

    return 0;
}
