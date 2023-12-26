#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <limits>
#include <string>
#include <cctype>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 3/" + type + ".txt");

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
    
    std::vector<std::vector<char>> grid;
    for (int i = 0; i < input.size(); i++) {
        std::vector<char> line;
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '\n') continue;
            line.push_back(input[i][j]);
        }
        grid.push_back(line);
    }
    
    int R = grid.size();
    int C = grid[0].size();

    std::vector<int> DR = {-1, 0, 1};
    std::vector<int> DC = {-1, 0, 1};

    std::map<std::vector<int>, std::vector<int>> gears;

    for (int r = 0; r < R; r++) {
        int n = 0;
        bool isPart = false;
        std::vector<int> currGear;
        for (int c = 0; c < C; c++) {
            char ch = grid[r][c];
            if (std::isdigit(ch)) {
                n = n*10 + ch - '0';
        
                if (isPart) continue;

                for (int dr : DR) {
                    for (int dc : DC) {
                        int rr = r + dr;
                        int cc = c + dc;

                        if (!(rr < R && rr >= 0) || !(cc < C && cc >=0)) continue;
                        if (dr == 0 && dc == 0) continue;

                        if (grid[rr][cc] == '*') {
                            gears[{rr, cc}];
                            currGear.push_back(rr);
                            currGear.push_back(cc);
                            isPart = true;
                            break;
                        }

                        // if (!std::isdigit(grid[rr][cc]) && grid[rr][cc] != '.') {
                        //     isPart = true;
                        //     break;
                        // }

                    }
                    if (isPart) break;
                }

            } else {
                if (isPart) gears[currGear].push_back(n);
                n = 0;
                isPart = false;
                currGear = {};
            }
        }
        if (isPart) gears[currGear].push_back(n);  
        n = 0;
        isPart = false;
        currGear = {};
        
    }

    for (const auto& gear : gears) {
    
        if (gear.second.size() == 2) {
            ans += gear.second[0] * gear.second[1];
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

