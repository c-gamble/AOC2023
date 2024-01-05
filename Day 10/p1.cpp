#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <stack>
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
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 10/" + type + ".txt");

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
    
    std::vector<std::string> graph = input;
    int sr, sc;
    for (int r = 0; r < graph.size(); r++) {
        bool innerDidBreak = false;
        for (int c = 0; c < graph[r].size(); c++) {
            if (graph[r][c] == 'S') {
                sr = r;
                sc = c;
                innerDidBreak = true;
                break;
            }
        }
        if (innerDidBreak) break;
    }

    std::set<std::pair<int, int>> seen;
    seen.insert(std::make_pair(sr, sc));

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(sr, sc));

    while (!q.empty()) {
        std::pair<int, int> currPos = q.front();
        q.pop();

        int r = currPos.first;
        int c = currPos.second;

        char currCh = graph[r][c];

        // check up
        if (r > 0 && (currCh == 'S' || currCh == '|' || currCh == 'J' || currCh == 'L') && (graph[r-1][c] == '|' || graph[r-1][c] == '7' || graph[r-1][c] == 'F') && seen.find(std::make_pair(r-1, c)) == seen.end()) {
            seen.insert(std::make_pair(r-1, c));
            q.push(std::make_pair(r-1, c));
        }

        // check down
        if (r < graph.size() && (currCh == 'S' || currCh == '|' || currCh == '7' || currCh == 'F') && (graph[r+1][c] == 'J' || graph[r+1][c] == '|' || graph[r+1][c] == 'L') && seen.find(std::make_pair(r+1, c)) == seen.end()) {
            seen.insert(std::make_pair(r+1, c));
            q.push(std::make_pair(r+1, c));
        }

        // check left
        if (c > 0 && (currCh == 'S' || currCh == '-' || currCh == 'J' || currCh == '7') && (graph[r][c-1] == '-' || graph[r][c-1] == 'L' || graph[r][c-1] == 'F') && seen.find(std::make_pair(r, c-1)) == seen.end()) {
            seen.insert(std::make_pair(r, c-1));
            q.push(std::make_pair(r, c-1));
        }   

        // check right
        if (c < graph[r].size() && (currCh == 'S' || currCh == '-' || currCh == 'L' || currCh == 'F') && (graph[r][c+1] == '-' || graph[r][c+1] == 'J' || graph[r][c+1] == '7') && seen.find(std::make_pair(r, c+1)) == seen.end()) {
            seen.insert(std::make_pair(r, c+1));
            q.push(std::make_pair(r, c+1));
        }        

    }

    ans = seen.size() / 2;
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

