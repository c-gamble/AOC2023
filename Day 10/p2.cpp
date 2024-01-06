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

    std::set<std::pair<int, int>> loop;
    loop.insert(std::make_pair(sr, sc));

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(sr, sc));

    std::set<char> possibleS;
    possibleS.insert('|');
    possibleS.insert('-');
    possibleS.insert('J');
    possibleS.insert('L');
    possibleS.insert('7');
    possibleS.insert('F');

    while (!q.empty()) {
        std::pair<int, int> currPos = q.front();
        q.pop();

        int r = currPos.first;
        int c = currPos.second;

        char currCh = graph[r][c];

        // check up
        if (r > 0 && (currCh == 'S' || currCh == '|' || currCh == 'J' || currCh == 'L') && (graph[r-1][c] == '|' || graph[r-1][c] == '7' || graph[r-1][c] == 'F') && loop.find(std::make_pair(r-1, c)) == loop.end()) {
            loop.insert(std::make_pair(r-1, c));
            q.push(std::make_pair(r-1, c));
            if (currCh == 'S') {
                std::set<char> copySet = possibleS;
                for (auto it = copySet.begin(); it != copySet.end(); ++it) {
                    if (*it != '|' && *it != 'J' && *it != 'L') {
                        possibleS.erase(*it);
                    }
                }
            }             
        }

        // check down
        if (r < graph.size() && (currCh == 'S' || currCh == '|' || currCh == '7' || currCh == 'F') && (graph[r+1][c] == 'J' || graph[r+1][c] == '|' || graph[r+1][c] == 'L') && loop.find(std::make_pair(r+1, c)) == loop.end()) {
            loop.insert(std::make_pair(r+1, c));
            q.push(std::make_pair(r+1, c));
            if (currCh == 'S') {
                std::set<char> copySet = possibleS;
                for (auto it = copySet.begin(); it != copySet.end(); ++it) {
                    if (*it != '|' && *it != '7' && *it != 'F') {
                        possibleS.erase(*it);
                    }
                }
            }            
        }

        // check left
        if (c > 0 && (currCh == 'S' || currCh == '-' || currCh == 'J' || currCh == '7') && (graph[r][c-1] == '-' || graph[r][c-1] == 'L' || graph[r][c-1] == 'F') && loop.find(std::make_pair(r, c-1)) == loop.end()) {
            loop.insert(std::make_pair(r, c-1));
            q.push(std::make_pair(r, c-1));
            if (currCh == 'S') {
                std::set<char> copySet = possibleS;
                for (auto it = copySet.begin(); it != copySet.end(); ++it) {
                    if (*it != '-' && *it != 'J' && *it != '7') {
                        possibleS.erase(*it);
                    }
                }
            }                        
        }   

        // check right
        if (c < graph[r].size() && (currCh == 'S' || currCh == '-' || currCh == 'L' || currCh == 'F') && (graph[r][c+1] == '-' || graph[r][c+1] == 'J' || graph[r][c+1] == '7') && loop.find(std::make_pair(r, c+1)) == loop.end()) {
            loop.insert(std::make_pair(r, c+1));
            q.push(std::make_pair(r, c+1));
            if (currCh == 'S') {
                std::set<char> copySet = possibleS;
                for (auto it = copySet.begin(); it != copySet.end(); ++it) {
                    if (*it != '-' && *it != 'L' && *it != 'F') {
                        possibleS.erase(*it);
                    }
                }
            }                        
        }        
    }

    assert (possibleS.size() == 1);
    char S = *possibleS.begin();
    
    // replace S with the right character
    graph[sr] = graph[sr].substr(0, sc) + S + graph[sr].substr(sc+1, graph[sr].size()-sc);

    std::vector<std::vector<char>> newGraph;
    for (int r = 0; r < graph.size(); r++) {
        std::vector<char> currRow;
        for (int c = 0; c < graph[r].size(); c++) {
            if (loop.find(std::make_pair(r, c)) == loop.end()) currRow.push_back('.');
            else currRow.push_back(graph[r][c]);
        }
        newGraph.push_back(currRow);
    }

    std::set<std::pair<int, int>> outside;
    for (int r = 0; r < newGraph.size(); r++) {
        bool within = false;
        bool up = false;
        for (int c = 0; c < newGraph[r].size(); c++) {
            char ch = newGraph[r][c];
            if (ch == '|') within = !within;
            else if (ch == 'F' || ch == 'L') up = (ch == 'L');
            else if (ch == '7' || ch == 'J') {
                if (up) {
                    if (ch != 'J') within = !within;
                } else {
                    if (ch != '7') within = !within;
                }
                up = false;
            }

            if (!within) outside.insert(std::make_pair(r, c));
        }
    }
    std::set<std::pair<int, int>> outsideUnionLoop;
    std::set_union(outside.begin(), outside.end(), loop.begin(), loop.end(), std::inserter(outsideUnionLoop, outsideUnionLoop.begin()));
    std::cout << newGraph.size() << " " << newGraph[0].size() << " " << outside.size() << " " << loop.size() << std::endl;
    ans = newGraph.size() * newGraph[0].size() - outsideUnionLoop.size();
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

