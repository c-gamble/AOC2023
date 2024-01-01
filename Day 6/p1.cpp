#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <stack>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 6/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;
    
    std::vector<int> times;
    std::vector<int> distances;

    int currTime = 0;
    for (int i = 0; i < input[0].size(); i++) {
        if (!std::isdigit(input[0][i]) && input[0][i] != ' ') {
            continue;
        } else if (input[0][i] == ' ') {
            if (currTime == 0) continue;
            else {
                times.push_back(currTime);
                currTime = 0;
                continue;
            }
        } else if (std::isdigit(input[0][i])) {
            currTime = currTime * 10 + input[0][i] - '0';
        }

        if (i == input[0].size() - 1) times.push_back(currTime);
    }

    int currDistance = 0;
    for (int i = 0; i < input[1].size(); i++) {
        if (!std::isdigit(input[1][i]) && input[1][i] != ' ') {
            continue;
        } else if (input[1][i] == ' ') {
            if (currDistance == 0) continue;
            else {
                distances.push_back(currDistance);
                currDistance = 0;
                continue;
            }
        } else if (std::isdigit(input[1][i])) {
            currDistance = currDistance * 10 + input[1][i] - '0';
        }

        if (i == input[1].size() - 1) distances.push_back(currDistance);
    }

    ans = 1;
    for (int i = 0; i < times.size(); i++) {
        int ways = 0;
        
        int currTime = times[i];
        int currDistance = distances[i];

        for (int chargeTime = 0; chargeTime < currTime; chargeTime++) {
            if ((currTime - chargeTime) * chargeTime > currDistance) ways++;
        }

        ans *= ways;
    }

    return std::to_string(ans);
}

int main(int argc, char** argv)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    std::string result = solve(argv);
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Runtime: " << ms_int.count() << "ms" << std::endl;
    return 0;
}

