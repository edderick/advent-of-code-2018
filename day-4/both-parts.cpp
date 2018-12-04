#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <regex>

using namespace std;

vector<string> getSortedEntries()
{
    vector<string> entries;
    for (string line; getline(cin, line); ) {
        entries.push_back(line);
    }
    sort(entries.begin(), entries.end());
    return entries;
}

int parseTime(const string& entry)
{        
    regex timeRegex("\\[\\d\\d\\d\\d-\\d\\d-\\d\\d \\d\\d:(\\d\\d)\\]");
    auto words_begin = sregex_iterator(entry.begin(), entry.end(), timeRegex);
    return stoi((*words_begin)[1]);
}

bool beginsShift(const string& entry)
{
    regex beginShiftRegex("Guard #(\\d+) begins shift");
    return std::regex_search(entry, beginShiftRegex);
}

int getGuardOnShift(const string& entry)
{
    regex beginShiftRegex("Guard #(\\d+) begins shift");
    auto words_begin = sregex_iterator(entry.begin(), entry.end(), beginShiftRegex);
    return stoi((*words_begin)[1]);
}

bool fallsAsleep(const string& entry)
{
    regex asleepRegex("falls asleep");
    return std::regex_search(entry, asleepRegex); 
}

bool wakesUp(const string& entry)
{
    regex wakeRegex("wakes up");
    return std::regex_search(entry, wakeRegex); 
}

void printPartOne(const unordered_map<int, unordered_map<int, int>>& sleepTimes)
{
    int yaBoi = 0; 
    int maxSleep = 0; 
    int theBestMinute = 0; 

    for (auto guard : sleepTimes)
    {
        int totalSleep = 0;
        int maxMinute = 0;
        int bestMinute = 0;
        for (auto time : guard.second)
        {
            totalSleep += time.second; 
            if (time.second > maxMinute)
            {
                maxMinute = time.second;
                bestMinute = time.first;
            }
        }
        if (totalSleep > maxSleep)
        {
            maxSleep = totalSleep;
            yaBoi = guard.first;
            theBestMinute = bestMinute;
        }
    }
    
    cout << "Part One: "
         << theBestMinute << " * " << yaBoi << " = " 
         << theBestMinute * yaBoi << "\n"; 
}

void printPartTwo(const unordered_map<int, unordered_map<int, int>>& sleepTimes)
{
    int yaBoi = 0; 
    int maxMinute = 0;
    int bestMinute = 0;

    for (auto guard : sleepTimes) {
        for (auto time : guard.second) {
            if (time.second > maxMinute) {
                maxMinute = time.second;
                bestMinute = time.first;
                yaBoi = guard.first;
            }
        }
    }
    
    cout << "Part Two: "
         << bestMinute << " * " << yaBoi << " = " 
         << bestMinute * yaBoi << "\n"; 
}

int main(int argc, char* argv[])
{
    const vector<string> entries = getSortedEntries();

    int guardOnShift = 0; 
    int previousTime = 0;
    unordered_map<int, unordered_map<int, int>> sleepTimes;

    for (auto entry : entries) {
        int time = parseTime(entry);

        if (beginsShift(entry)) {
            guardOnShift = getGuardOnShift(entry);
        }
        else if (fallsAsleep(entry)) {
            previousTime = time;
        }
        else if (wakesUp(entry)) {
            for (int t = previousTime; t < time; t++)
            {
                sleepTimes[guardOnShift][t]++;
            }
        }
    }
    
    printPartOne(sleepTimes);
    printPartTwo(sleepTimes);
    return 0;
}
