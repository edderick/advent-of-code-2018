#include <iostream>
#include <vector>

using namespace std;

struct Result {
    Result() : sumOfMetadata(0), endIndex(0) {};
    int sumOfMetadata;
    int endIndex;
};

Result sumMetadata(const vector<int>& input, int root) {
    Result r;

    int it = root;
    int numChildren = input[it];

    it++;
    int numMetadata = input[it];

    for (int i = 0; i < numChildren; i++) {
       it++;
       Result childResult = sumMetadata(input, it);
       it = childResult.endIndex;
       r.sumOfMetadata += childResult.sumOfMetadata;
    }

    for (int i = 0; i < numMetadata; i++) {
        it++;
        r.sumOfMetadata += input[it];
    }
    
    r.endIndex = it;
    return r;
}

int main(int argc, char* argv[]) {
    vector<int> input;
    int i;
    while (cin >> i) {
        input.push_back(i);
    }

    cout << sumMetadata(input, 0).sumOfMetadata << "\n";
    return 0;
}
