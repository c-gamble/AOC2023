#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <string>
#include <numeric>
#include <algorithm>
#include <stack>
#include <cctype>
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

bool existsActiveNodes(std::vector<std::vector<std::string>> currNodes) {
    for (std::vector<std::string> node : currNodes) {
        if (node[1] == "active") return true;
    }
    return false;
}

long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long lcm(std::vector<long long> numbers)
{
    auto calculateLCM = [](long long a, long long b) {
        return (a * b) / gcd(a, b);
    };

    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = calculateLCM(result, numbers[i]);
    }
    return result;
}

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    long long ans = 0;
    
    std::vector<long long> instr;
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

    std::vector<std::vector<std::string>> currNodes;
    for (auto it = nodeMap.cbegin(); it != nodeMap.cend(); it++) {
        if (it->first[it->first.size()-1] != 'A') continue;
        else currNodes.push_back({it->first, "active", "0"}); // node, isActive, n_steps
    }
    while (existsActiveNodes(currNodes)) {
        int index = ans % instr.size();
        for (int i = 0; i < currNodes.size(); i++) {
            std::vector<std::string> node = currNodes[i];
            if (node[1] != "active") continue;
            if (node[0][2] == 'Z') {
                currNodes[i][0] = node[0].substr(0, 2) + "Z";
                currNodes[i][1] = "inactive";
                currNodes[i][2] = std::to_string(ans);
            }
            if (instr[index] == 0) currNodes[i][0] = nodeMap[node[0]].first;
            else if (instr[index] == 1) currNodes[i][0] = nodeMap[node[0]].second;
        }
        ans++;
    }

    std::vector<long long> stepCounts;
    for (std::vector<std::string> node : currNodes) stepCounts.push_back(std::stoll(node[2]));
    
    ans = lcm(stepCounts);
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

