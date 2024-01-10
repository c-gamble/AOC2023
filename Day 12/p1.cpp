#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <queue>
#include <numeric>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 12/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}


bool containsChar(std::string s, char target) {
    for (int c = 0; c < s.size(); c++) {
        if (s[c] == target) return true;
    }
    return false;
}

bool fits(std::string configuration, int startIdx, int endIdx) {
    if (((startIdx - 1) < 0) || ((endIdx+1) >= configuration.size())) return false;

    if (configuration[startIdx-1] == '#' || configuration[endIdx+1] == '#') return false;

    if (containsChar(configuration.substr(0, startIdx), '#')) return false;

    for (int i = startIdx; i <= endIdx; i++) {
        if (configuration[i] == '.') return false;
    }

    return true;
}

int countArrangements(std::string configuration, std::vector<int> groups) {
    if (groups.size() == 0) {
        return (containsChar(configuration, '#')) ? 0 : 1;
    }

    int size = groups[0];
    std::vector<int> newGroups(groups.begin()+1, groups.end());

    int ret = 0;
    for (int endIdx = 0; endIdx < configuration.size(); endIdx++) {
        int startIdx = endIdx - (size - 1);

        if (fits(configuration, startIdx, endIdx)) {
            ret += countArrangements(configuration.substr(endIdx+1), newGroups);
        }
    }
    return ret;
}

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;

    std::vector<std::string> configurations;
    std::vector<std::vector<int>> groups;

    for (int i = 0; i < input.size(); i++) {
        bool hitSpace = false;
        int currN = 0;
        std::vector<int> currGroup;
        for (int j = 0; j < input[i].size(); j++) {
            char ch = input[i][j];

            if (ch == ' ') {
                hitSpace = true;
                configurations.push_back(input[i].substr(0, j));
            } else if (hitSpace) {
                if (std::isdigit(ch)) currN = currN * 10 +  ch - '0';
                else if (ch == ',') {
                    currGroup.push_back(currN);
                    currN = 0;
                }
            } 

            if (j == input[i].size()-1) {
                currGroup.push_back(currN);
            }
        }
        groups.push_back(currGroup);
    }

    for (int i = 0; i < configurations.size(); i++) {
        ans += countArrangements("." + configurations[i] + ".", groups[i]);
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

