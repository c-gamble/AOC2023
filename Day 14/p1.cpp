// solution credit to @programmingproblems on youtube
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
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 14/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}

std::vector<std::vector<char>> tiltGrid(std::vector<std::vector<char>> grid) {
    int R = grid.size(), C = grid[0].size();
    std::vector<std::vector<char>> newGrid(R, std::vector<char> (C));
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == '#') newGrid[r][c] = '#';
            else newGrid[r][c] = '.';
        }
    }

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 'O') {
                int rowUp = r;
                while (rowUp >= 0 && newGrid[rowUp][c] == '.') {
                    rowUp--;
                }
                newGrid[rowUp+1][c] = 'O';
            }
        }
    }

    return newGrid;
}
std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;

    std::vector<std::vector<char>> grid;
    for (int r = 0; r < input.size(); r++) {
        std::vector<char> currRow;
        for (int c = 0; c < input[r].size(); c++) {
            currRow.push_back(input[r][c]);
        }
        grid.push_back(currRow);
    }

    grid = tiltGrid(grid);
    for (int r = 0; r < grid.size(); r++) {
        int Ocount = 0;
        for (char c : grid[r]) {
            if (c == 'O') Ocount++;
        }
        ans += (grid.size()-r)*Ocount;
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

