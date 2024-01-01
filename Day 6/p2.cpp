#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <string>
#include <algorithm>
#include <stack>
#include <cctype>
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
    
    int time = 0;
    for (int i = 0; i < input[0].size(); i++) {
        if (!std::isdigit(input[0][i])) {
            continue;
        } else {
            time = time * 10 + input[0][i] - '0';
        }

    }

    int distance = 0;
    for (int i = 0; i < input[1].size(); i++) {
        if (!std::isdigit(input[1][i])) {
            continue;
        } else {
            distance = distance * 10 + input[1][i] - '0';
        }

    }


    for (int chargeTime = 0; chargeTime < time; chargeTime++) {
            if ((time - chargeTime) * chargeTime > distance) ans++;
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

