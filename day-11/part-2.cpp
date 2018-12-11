#include <iostream>

using namespace std;

int powerLevel(int x, int y, int serialNumber) {
    return ((((((x + 10) * y) + serialNumber) * (x + 10)) / 100) % 10) - 5;
}

// Based on a Summed-area table
int main(int argc, char* argv[]) {
    long input; cin >> input;
    int arr[301][301] = {0};

    for (int i = 1; i < 301; i++) {
        for (int j = 1; j < 301; j++) {
            int level = powerLevel(i, j, input);
            arr[i][j] = level + arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
        }
    }

    int maxSum = 0; int maxX = 0; int maxY = 0; int maxSize = 0;

    for (int s = 1; s < 300; s++) {
        for (int i = 1; i < 301 - s; i++) {
            for (int j = 1; j < 301 - s; j++) {
                int sum = arr[i + s][j + s] + arr[i][j] - arr[i + s][j] - arr[i][j + s]; 
                if (sum > maxSum) {
                    maxX = i; 
                    maxY = j;
                    maxSum = sum;
                    maxSize = s;
                }
            }
        }
    }

    cout << maxX + 1 << "," << maxY + 1 << "," << maxSize <<  "\n"; 
    return 0;
}
