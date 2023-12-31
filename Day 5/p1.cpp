#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 5/" + type + ".txt");

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

    double ans = 0;
    
    std::vector<double> seeds;
    std::vector<std::vector<std::vector<double>>> maps; // { { {dest, source, length}, {dest, source, length} } }
    std::vector<std::vector<double>> currMap;

    for (double i = 0; i < input.size(); i++) {
        if (i == 0) {
            double currSeed = 0;
            for (double j = 7; j < input[i].size(); j++) {
                if (std::isdigit(input[i][j])) {
                    currSeed = currSeed * 10 + input[i][j] - '0';
                } else if (input[i][j] == ' ') {
                    seeds.push_back(currSeed);
                    currSeed = 0;
                    continue;
                } 

                if (j == input[i].size() - 1) seeds.push_back(currSeed);
            }
        } else if (i == 1) continue;
        
        if (input[i].size() == 0) {
            maps.push_back(currMap);
            currMap = {};
            continue;
        } else if (!std::isdigit(input[i][0])) continue;
        else {
            std::vector<double> currLine = {};
            double currValue = 0;
            for (double j = 0; j < input[i].size(); j++) {
                if (std::isdigit(input[i][j])) {
                    currValue = currValue * 10 + input[i][j] - '0';
                } else if (input[i][j] == ' ') {
                    currLine.push_back(currValue);
                    currValue = 0;
                    continue;
                }
                if (j == input[i].size() - 1) currLine.push_back(currValue);
            }
            currMap.push_back(currLine);
        }

        if (i == input.size() - 1) maps.push_back(currMap);

    }
    std::vector<double> locationNums;
    for (double seed : seeds) {
        for (double i = 0; i < maps.size(); i++) {
            std::vector<std::vector<double>> currMap = maps[i];
            for (double j = 0; j < currMap.size(); j++) {
                std::vector<double> currRange = currMap[j];
                if ((seed >= currRange[1]) && (seed < currRange[1] + currRange[2])) {
                    double diff = currRange[0] - currRange[1];
                    seed += diff;
                    break;
                }
            }
        } 
        locationNums.push_back(seed);
    }
    ans = 100000000;
    for (double loc : locationNums) ans = std::min(ans, loc);
    return std::to_string((int) ans);
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

