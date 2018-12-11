#include <iostream>

using namespace std;

int powerLevel(int x, int y, int serialNumber) {
    return ((((((x + 10) * y) + serialNumber) * (x + 10)) / 100) % 10) - 5;
}

int main(int argc, char* argv[]) {
    long input; cin >> input;
    int arr[301][301] = {0};

    for (int i = 1; i < 301; i++) {
        for (int j = 1; j < 301; j++) {
            arr[i][j] = powerLevel(i, j, input);
        }
    }

    int maxSum = 0; int maxX = 0; int maxY = 0;

    for (int i = 1; i < 301 - 3; i++) {
        for (int j = 1; j < 301 - 3; j++) {
            int sum = 0; 
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++ ) {
                    sum += arr[i + x][j + y];
                }
            }
            if (sum > maxSum) {
                maxX = i; 
                maxY = j;
                maxSum = sum;
            }
        }
    }

    cout << maxX << ", " << maxY << "\n"; 
    return 0;
}
