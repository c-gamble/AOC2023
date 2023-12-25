#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 2/" + type + ".txt");

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
    
    int RED = 12;
    int GREEN = 13;
    int BLUE = 14;

    for (int i = 0; i < input.size(); i++) {
        int red = 0;
        int green = 0;
        int blue = 0;
        
        int gameId;

        int windowStart = 0;
        while (windowStart < input[i].size()) {
            int windowEnd = windowStart + 1;
            while (windowEnd <= input[i].size()) {
                std::string window = input[i].substr(windowStart, windowEnd-windowStart);
                if (window.find("Game ") != std::string::npos) {
                    std::string gameWindow = window;
                    int gameIter = 1;
                    while (gameWindow.find(":") == std::string::npos) {
                        gameWindow += input[i].substr(windowEnd, gameIter);
                        gameIter++;
                    }
                    gameId = std::stoi(input[i].substr(windowEnd, gameIter));
                    windowStart = windowEnd;
                    break;
                } else if (window.find("blue") != std::string::npos) {
                    std::string blueWindow = input[i].substr(windowEnd-6, 1);
                    int blueIter = 1;
                    while (blueWindow.find(" ") == std::string::npos) {
                        blueWindow = input[i].substr(windowEnd-6-blueIter, 1) + blueWindow;
                        blueIter++;
                    }
                    int currBlue = std::stoi(input[i].substr(windowEnd-5-blueIter, blueIter));
                    blue = std::max(blue, currBlue);
                    windowStart = windowEnd;
                    break;
                } else if (window.find("green") != std::string::npos) {
                    std::string greenWindow = input[i].substr(windowEnd-7, 1);
                    int greenIter = 1;
                    while (greenWindow.find(" ") == std::string::npos) {
                        greenWindow = input[i].substr(windowEnd-7-greenIter, 1) + greenWindow;
                        greenIter++;
                    }
                    int currGreen = std::stoi(input[i].substr(windowEnd-6-greenIter, greenIter));
                    green = std::max(green, currGreen);
                    windowStart = windowEnd;
                    break;
                } else if (window.find("red") != std::string::npos) {
                    if (i==3) std::cout << windowStart << std::endl;
                    std::string redWindow = input[i].substr(windowEnd-5, 1);
                    int redIter = 1;
                    while (redWindow.find(" ") == std::string::npos) {
                        redWindow = input[i].substr(windowEnd-5-redIter, 1) + redWindow;
                        redIter++;
                    }
                    int currRed = std::stoi(input[i].substr(windowEnd-4-redIter, redIter));
                    red = std::max(red, currRed);
                    windowStart = windowEnd;
                    break;
                } else {
                    windowEnd++;
                    continue;
                }
            }
            
            windowStart++;
        }
        if (red <= RED && blue <= BLUE && green <= GREEN) {
            ans += gameId;
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

    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Runtime: " << ms_int.count() << "ms" << std::endl;
    return 0;
}

