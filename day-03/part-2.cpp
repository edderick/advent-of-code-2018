#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const int BOUNDS = 1000;

int main(int argc, char* argv[]) {
    char c;
    int grid[BOUNDS][BOUNDS] = {0};

    struct Claim {
        int id;
        int x;
        int y; 
        int width;
        int height;
    };

    vector<Claim> candidateClaims;

    while (cin >> c) {
        Claim claim;
        cin >> claim.id >> c >> claim.x >> c >> claim.y >> c >> claim.width >> c >> claim.height;

        bool possible = true;

        for (int i = claim.x; i < (claim.x + claim.width); i++) {
            for (int j = claim.y; j < (claim.y + claim.height); j++) {
                if (i > BOUNDS || j > BOUNDS) {
                    cout << "Out of bounds?! (" << i << "," << j << ")\n";
                    return -1;
                }

                grid[i][j] += 1;

                if (grid[i][j] > 1) {
                    possible = false;
                }
            }
        }
        if (possible)
        {
            candidateClaims.push_back(claim);
        }
    }

    for (const auto& claim : candidateClaims)
    {
        bool possible = true;
        for (int i = claim.x; i < (claim.x + claim.width); i++) {
            for (int j = claim.y; j < (claim.y + claim.height); j++) {
                if (grid[i][j] > 1) {
                    possible = false;
                    break;
                }
            }
            if (!possible)
            {
                break;
            }
        }
        if (possible)
        {
            cout << claim.id << "\n";
            return 0; 
        }
    }

    return 0;
}
