#include <iostream>
#include <vector>

using namespace std;

struct Result {
    Result() : sumOfMetadata(0), endIndex(0) {};
    int sumOfMetadata;
    int endIndex;
};

Result sumMetadata(const vector<int>& input, int root)
{
    Result r;

    int it = root;
    int numChildren = input[it];

    it++;
    int numMetadata = input[it];

    if (numChildren == 0) {
        for (int i = 0; i < numMetadata; i++) {
            it++;
            r.sumOfMetadata += input[it];
        }
    }
    else {
        vector<int> childResults; 
        for (int i = 0; i < numChildren; i++) {
           it++;
           Result childResult = sumMetadata(input, it);
           it = childResult.endIndex;
           childResults.push_back(childResult.sumOfMetadata);
        }
        for (int i = 0; i < numMetadata; i++) {
            it++;
            if (input[it] - 1 < childResults.size()) {
                 r.sumOfMetadata += childResults[input[it] - 1];
            }
        }
    }
    
    r.endIndex = it;
    return r;
}


int main(int argc, char* argv[])
{
    vector<int> input;
    int i;
    while (cin >> i) {
        input.push_back(i);
    }

    cout << sumMetadata(input, 0).sumOfMetadata << "\n";
    return 0;
}
