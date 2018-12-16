#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void printCircle(const list<int>::iterator& current, const list<int>& circle) {
    for (auto it = circle.begin(); it != circle.end(); ++it) {
        if (it == current) {
            cout << "(" << *it << ") ";
        }
        else {
            cout << *it << " "; 
        }
    }
    cout << "\n";
}

void moveClockwise(list<int>::iterator& it, const list<int>& circle) {
    if (it == circle.end()) {
        it = const_cast<list<int>&>(circle).begin();
    }
    it++;
}

void moveAntiClockwise(list<int>::iterator& it, const list<int>& circle)
{
    if (it == circle.begin()) {
        it = const_cast<list<int>&>(circle).end();
    }
    it--;
}

int main(int argc, char* argv[])
{
    int NUM_PLAYERS = 462; 
    int LAST_MARBLE = 71938 * 100;

    bool VERBOSE = false;

    vector<long> scores(NUM_PLAYERS, 0);
    list<int> circle(1, 0);
    list<int>::iterator current = circle.begin();

    if (VERBOSE) {
        cout << "[" << "-" << "] ";
        printCircle(current, circle);
    }

    for (int round = 1; round <= LAST_MARBLE; ++round) {
        int player = ((round - 1) % NUM_PLAYERS) + 1;
        if (round % 23 == 0) {
            scores[player - 1] += round;
            for (int i = 0; i < 7; ++i) {
                moveAntiClockwise(current, circle);
            }
            scores[player - 1] += *current;
            current = circle.erase(current);
            if (current == circle.end()) {
                current = circle.begin();
            }
        }
        else {
            moveClockwise(current, circle);
            moveClockwise(current, circle);
            current = circle.insert(current, round);
        }

        if (VERBOSE) {
            cout << "[" << player << "] ";
            printCircle(current, circle);
        }
    }

    cout << *max_element(scores.begin(), scores.end()) << "\n";
    return 0;
}
