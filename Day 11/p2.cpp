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
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 11/" + type + ".txt");

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

    long long ans = 0;
    
    std::vector<std::string> graph = input;
    std::vector<int> emptyRows, emptyCols;
    std::vector<std::pair<int, int>> galaxies;

    for (int r = 0; r < graph.size(); r++) {
        bool rowIsEmpty = true;
        for (int c = 0; c < graph[r].size(); c++) {
            if (graph[r][c] != '.') rowIsEmpty = false;
            if (graph[r][c] == '#') galaxies.push_back(std::make_pair(r, c));
        }
        if (rowIsEmpty) emptyRows.push_back(r);
    }

    for (int c = 0; c < graph[0].size(); c++) {
        bool colIsEmpty = true;
        for (int r = 0; r < graph.size(); r++) {
            if (graph[r][c] != '.') colIsEmpty = false;
        }
        if (colIsEmpty) emptyCols.push_back(c);
    }

    long long scaleFactor = 1000000;
    for (int i = 0; i < galaxies.size(); i++) {
        std::pair<int, int> galaxy = galaxies[i];
        int r1 = galaxy.first;
        int c1 = galaxy.second;

        for (int j = 0; j < i; j++) {
            std::pair<int, int> otherGalaxy = galaxies[j];
            int r2 = otherGalaxy.first;
            int c2 = otherGalaxy.second;

            for (int r = std::min(r1, r2); r < std::max(r1, r2); r++) {
                if (std::find(emptyRows.begin(), emptyRows.end(), r) != emptyRows.end()) {
                     ans += scaleFactor;   
                }
                else {
                    ans += 1;
                }
            }
            for (int c = std::min(c1, c2); c < std::max(c1, c2); c++) {
                if (std::find(emptyCols.begin(), emptyCols.end(), c) != emptyCols.end()) {
                    ans += scaleFactor;
                }
                else {
                    ans += 1;
                }
            }

        }
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

