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
    
    for (int i = 0; i < input.size(); i++) {
        std::string digits = "";
        for (int cidx = 0; cidx < input[i].size(); cidx++) {
            if (std::isdigit(input[i][cidx])) {
                digits += input[i][cidx];
            }
        }
        std::string kept;
        if (digits.size() > 1) {
            kept = digits.substr(0,1) + digits.substr(digits.size()-1, 1);
        } else {
            kept = digits + digits;
        }
        ans += std::stoi(kept);
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
