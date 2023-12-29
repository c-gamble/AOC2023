#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>
#include <algorithm>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 4/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}

int countOverlaps(std::vector<int> a, std::vector<int> b) {
    int totalOverlaps = 0;

    for (int aNum : a) {
        if (std::find(b.begin(), b.end(), aNum) != b.end()) {
            totalOverlaps += 1;
        }
    }
    
    return totalOverlaps;
}

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;
    
    for (int i = 0; i < input.size(); i++) {
        std::vector<int> myCards;
        std::vector<int> winningCards;

        int currN = 0;
        bool isLeft = true;
        for (int chIdx = 8; chIdx < input[i].size(); chIdx++) {
            char ch = input[i][chIdx];

            if (ch == ' ') {
                char prevCh = input[i][chIdx-1];
                if (std::isdigit(prevCh)) {
                    if (isLeft) winningCards.push_back(currN);
                    else myCards.push_back(currN);
                    currN = 0;
                    continue;
                } else continue;
            } else if (std::isdigit(ch)) {
                currN = currN * 10 + ch - '0';
            } else if (ch == '|') {
                isLeft = false;
                continue;
            }

            if (chIdx == input[i].size() - 1) {
                myCards.push_back(currN);
                break;
            }
        }
        int nWinning = countOverlaps(myCards, winningCards);
        if (nWinning == 0) continue;
        else ans += pow(2, (nWinning - 1));
        
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

