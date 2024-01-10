// solution credit to https://www.youtube.com/@programmingproblems
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
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 13/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}

bool isFixable(std::string r1, std::string r2) {
    int diffs = 0;

    for (int i = 0; i < r1.size(); i++) {
        if (r1[i] != r2[i]) diffs++;
    }

    return (diffs == 1);
}
bool isReflection(std::vector<std::string> grid, int start) {
    int lower = start;
    int upper = start + 1;
    bool wasFixed = false;

    while (lower >= 0 && upper < grid.size()) { 
        if (grid[lower] != grid[upper]) {
            if (wasFixed) return false;
            else if (isFixable(grid[lower], grid[upper])) wasFixed = true;
            else return false;
        }
        lower--;
        upper++;
    }
    
    return wasFixed;
}

int findReflection(std::vector<std::string> grid) {
    for (int r = 0; r < grid.size() - 1; r++) {
        if (isReflection(grid, r)) return r + 1;
    }
    return 0;
}

std::vector<std::string> transpose(std::vector<std::string> grid) {
    std::vector<std::string> transposedGrid;
    for (int c = 0; c < grid[0].size(); c++) {
        std::string currCol = "";
        for (int r = 0; r < grid.size(); r++) {            
            currCol += grid[r][c];
        }
        transposedGrid.push_back(currCol);
    }
    return transposedGrid;
}

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;
    
    std::vector<std::vector<std::string>> grids;

    std::vector<std::string> currGrid;
    for (int i = 0; i < input.size(); i++) {
        
        if (input[i] == "") {
            grids.push_back(currGrid);
            currGrid.clear();
            continue;
        } else if (i == input.size()-1) {
            currGrid.push_back(input[i]);
            grids.push_back(currGrid);
            break;
        }

        currGrid.push_back(input[i]);
    }

    for (std::vector<std::string> grid : grids) {
        int r = findReflection(grid);
        ans += r*100;
        ans += findReflection(transpose(grid));

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

