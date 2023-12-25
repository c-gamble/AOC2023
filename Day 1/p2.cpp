#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 1/" + type + ".txt");

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

    std::map<std::string, int> windowMap;
    windowMap["one"] = 1;
    windowMap["two"] = 2;
    windowMap["three"] = 3;
    windowMap["four"] = 4;
    windowMap["five"] = 5;
    windowMap["six"] = 6;
    windowMap["seven"] = 7;
    windowMap["eight"] = 8;
    windowMap["nine"] = 9;
    windowMap["1"] = 1;
    windowMap["2"] = 2;
    windowMap["3"] = 3;
    windowMap["4"] = 4;
    windowMap["5"] = 5;
    windowMap["6"] = 6;
    windowMap["7"] = 7;
    windowMap["8"] = 8;
    windowMap["9"] = 9;

    for (int lineIdx = 0; lineIdx < input.size(); lineIdx++) {
        std::vector<int> foundDigits;
        for (int windowStart = 0; windowStart < input[lineIdx].size(); windowStart++) {
            int windowEnd = windowStart+1;
            while (windowEnd <= input[lineIdx].size()) {
                std::string window = input[lineIdx].substr(windowStart, windowEnd-windowStart);
                if (windowMap.find(window) != windowMap.end()) {
                    foundDigits.push_back(windowMap[window]);
                    break;
                }
                windowEnd++;
            }
        }
        std::vector<int> finalNums;
        if (foundDigits.size() > 1) {
            finalNums.push_back(foundDigits[0]*10 + foundDigits[foundDigits.size()-1]);
        } else {
            finalNums.push_back(foundDigits[0]*10 + foundDigits[0]);
        }
        for (int i = 0; i < finalNums.size(); i++) ans += finalNums[i];  
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

    std::cout << "Part 2: " << result << std::endl;
    std::cout << "Runtime: " << ms_int.count() << "ms" << std::endl;
    return 0;
}
