#include <iostream>
#include <string>

using namespace std;

static const int BOUNDS = 1000;

int main(int argc, char* argv[]) {
    char c;
    int grid[BOUNDS][BOUNDS] = {0};

    int count = 0;

    while (cin >> c) {
        int id, x, y, width, height;
        cin >> id >> c >> x >> c >> y >> c >> width >> c >> height;

        for (int i = x; i < (x + width); i++) {
            for (int j = y; j < (y + height); j++) {
                if (i > BOUNDS || j > BOUNDS) {
                    cout << "Out of bounds?! (" << i << "," << j << ")\n";
                    return -1;
                }

                grid[i][j] += 1;

                if (grid[i][j] == 2) {
                    count++;
                }
            }
        }
    }

    cout << count << "\n";
    return 0;
}
