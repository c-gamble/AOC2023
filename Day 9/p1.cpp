#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <stack>
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
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 9/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}

bool isZero(std::vector<long long> seq) {
    for (long long n : seq) {
        if (n != 0) return false;
    }
    return true;
}

long long zeroDiff(std::vector<long long> currSeq, std::vector<std::vector<long long>> prevSeqs) {
    if (isZero(currSeq)) {
        long long val = 0;
        for (int i = prevSeqs.size()-1; i >= 0; i--) {
            val += prevSeqs[i][prevSeqs[i].size()-1];
        }
        return val;
    }

    std::vector<long long> newSeq;
    for (int i = 1; i < currSeq.size(); i++) {
        newSeq.push_back(currSeq[i]-currSeq[i-1]);
    }
    prevSeqs.push_back(currSeq);
    return zeroDiff(newSeq, prevSeqs);
}

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;
    
    std::vector<std::vector<long long>> sequences;
    for (int i = 0; i < input.size(); i++) {
        std::vector<long long> currSeq;
        long long currN = 0;
        bool isNegative = false;
        for (int j = 0; j < input[i].size(); j++) {
            if (std::isdigit(input[i][j])) {
                currN = currN * 10 + input[i][j] - '0';
            } else if (input[i][j] == '-') isNegative = true; 
            else {
                if (isNegative) currSeq.push_back(currN*-1);
                else currSeq.push_back(currN);
                currN = 0;
                isNegative = false;
                continue;
            }

            if (j == input[i].size() - 1) {
                if (isNegative) currSeq.push_back(currN*-1);
                else currSeq.push_back(currN);
            }
        }
        sequences.push_back(currSeq);
    }

    for (auto seq : sequences) {
        ans += zeroDiff(seq, {});
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

