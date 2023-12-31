// Solution credit to @JonathanPaulson on YouTube

#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <stack>

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

    class Map {
        public:
            std::vector<std::vector<double>> lines;

            Map(std::vector<std::vector<double>> processedLines) {
                lines = processedLines;
            } 

            std::stack<std::vector<double>> map(std::stack<std::vector<double>> ranges) {
                
                std::stack<std::vector<double>> mappedRanges;

                for (std::vector<double> line : lines) {
                    double dest = line[0];
                    double source = line[1];
                    double length = line[2];
                    double sourceEnd = source + length;

                    std::stack<std::vector<double>> newRanges;

                    while (!ranges.empty()) {
                        std::vector<double> currRange = ranges.top();
                        ranges.pop();
                        // std::cout << currRange[0] << " " << currRange[1] << std::endl;
                        double start = currRange[0];
                        double end = currRange[1];

                        std::vector<double> before = {start, std::min(end, source)};    
                        std::vector<double> inter = {std::max(start, source), std::min(sourceEnd, end)};
                        std::vector<double> after = {std::max(start, sourceEnd), end};

                        if (before[1] > before[0]) {
                            newRanges.push(before);
                        }
                        if (inter[1] > inter[0]) {
                            mappedRanges.push({inter[0]-source+dest, inter[1]-source+dest});
                        }
                        if (after[1] > after[0]) {
                            newRanges.push(after);
                        }
                    }
                    ranges = newRanges;
                }
                while (!ranges.empty()) {
                    mappedRanges.push(ranges.top());
                    ranges.pop();
                }
            
                return mappedRanges;
            }
    };

    std::vector<std::vector<double>> seedPairs;
    for (int i = 0; i < seeds.size() - 1; i+=2) {
        seedPairs.push_back({seeds[i], seeds[i+1]});
    }

    std::vector<Map> mapObjects;
    for (int i = 0; i < maps.size(); i++) {
        Map currMap(maps[i]);
        mapObjects.push_back(currMap);
    }

    std::vector<double> locationIntervals;
    for (int i = 0; i < seedPairs.size(); i++) {
        double rangeStart = seedPairs[i][0];
        double rangeLength = seedPairs[i][1];

        std::stack<std::vector<double>> r;
        r.push({rangeStart, rangeStart + rangeLength});

        for (Map map : maps) {
            r = map.map(r);
        }

        double minIntervalStart = 1000000000;
        std::stack<std::vector<double>> rCopy = r;
        while (!rCopy.empty()) {
            std::vector<double> currInterval = rCopy.top();
            rCopy.pop();
            minIntervalStart = std::min(minIntervalStart, currInterval[0]);
        }

        locationIntervals.push_back(minIntervalStart);
    }

    ans = 1000000000;
    for (double loc : locationIntervals) {
        ans = std::min(loc, ans);
    }

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

    std::cout << "Part 2: " << result << std::endl;
    std::cout << "Runtime: " << ms_int.count() << "ms" << std::endl;
    return 0;
}

