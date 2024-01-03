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
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 8/" + type + ".txt");

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
    
    std::vector<int> instr;
    for (int i = 0; i < input[0].size(); i++) {
        if (input[0][i] == 'R') instr.push_back(1);
        if (input[0][i] == 'L') instr.push_back(0);
    }

    std::map<std::string, std::pair<std::string, std::string>> nodeMap;
    for (int i = 2; i < input.size(); i++) {
        std::string source = input[i].substr(0, 3);
        std::pair<std::string, std::string> dest;
        dest.first = input[i].substr(7, 3);
        dest.second = input[i].substr(12, 3);

        nodeMap[source] = dest;
    }

    std::string currNode = "AAA";
    while (currNode != "ZZZ") {
        int index = ans % instr.size();
        if (instr[index] == 0) currNode = nodeMap[currNode].first;
        else if (instr[index] == 1) currNode = nodeMap[currNode].second;

        if (currNode == "ZZZ") break;
        
        ans++;
    }

    return std::to_string(ans+1);
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

