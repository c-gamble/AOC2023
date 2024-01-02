#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <stack>
#include <string>
#include <cctype>
#include <limits>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


std::vector<std::string> getInput(std::string type) {
    
    std::fstream inFile("/Users/coopergamble/code/comps/aoc/2023/Day 7/" + type + ".txt");

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    return lines;
}

bool five(std::vector<char> h) {
    for (int c = 0; c < h.size(); c++) {
        if (h[c] != h[0]) return false;
    }
    return true;
}

bool four(std::vector<char> h) {
    std::map<char, int> freqs;
    for (int c = 0; c < h.size(); c++) {
        if (freqs.find(h[c]) == freqs.end()) {
            freqs[h[c]] = 1;
        } else {
            freqs[h[c]]++;
        }
        if (freqs[h[c]] == 4) return true;
    }
    if (freqs[h[h.size()-1]] == 4) return true;
    return false;
}

bool fullHouse(std::vector<char> h) {
    std::map<char, int> freqs;
    for (int c = 0; c < h.size(); c++) {
        if (freqs.find(h[c]) == freqs.end()) {
            freqs[h[c]] = 1;
        } else {
            freqs[h[c]]++;
        }
    }
    if (freqs.size() != 2) return false;
    
    bool isTwo = false;
    bool isThree = false;
    for(auto it = freqs.cbegin(); it != freqs.cend(); it++) {
        if (it->second == 2) isTwo = true;
        else if (it-> second == 3) isThree = true;
    }
    return isTwo && isThree;
}

bool three(std::vector<char> h) {
    std::map<char, int> freqs;
    for (int c = 0; c < h.size(); c++) {
        if (freqs.find(h[c]) == freqs.end()) {
            freqs[h[c]] = 1;
        } else {
            freqs[h[c]]++;
        }
        if (freqs[h[c]] == 3) return true;
    }
    if (freqs[h[h.size()-1]] == 3) return true;
    return false;
}

bool twoPairs(std::vector<char> h) {
    std::map<char, int> freqs;
    for (int c = 0; c < h.size(); c++) {
        if (freqs.find(h[c]) == freqs.end()) {
            freqs[h[c]] = 1;
        } else {
            freqs[h[c]]++;
        }
    }
    int pairCount = 0;
    for (auto it = freqs.cbegin(); it != freqs.cend(); it++) {
        if (it->second == 2) pairCount++;
    }
    return pairCount == 2;
}

bool onePair(std::vector<char> h) {
    std::map<char, int> freqs;
    for (int c = 0; c < h.size(); c++) {
        if (freqs.find(h[c]) == freqs.end()) {
            freqs[h[c]] = 1;
        } else {
            freqs[h[c]]++;
        }
    }
    int pairCount = 0;
    for (auto it = freqs.cbegin(); it != freqs.cend(); it++) {
        if (it->second == 2) pairCount++;
    }
    return pairCount == 1;
}

bool high(std::vector<char> h) {
    std::map<char, int> freqs;
    for (int c = 0; c < h.size(); c++) {
        if (freqs.find(h[c]) == freqs.end()) {
            freqs[h[c]] = 1;
        } else {
            freqs[h[c]]++;
        }
    }
    for (auto it = freqs.cbegin(); it != freqs.cend(); it++) {
        if (it->second != 1) return false;
    }
    return true;
}

std::pair<int, std::vector<char>> rankHand(std::vector<char> hand) {
    if (five(hand)) return std::make_pair(7, hand);
    else if (four(hand)) return std::make_pair(6, hand);
    else if (fullHouse(hand)) return std::make_pair(5, hand);
    else if (three(hand)) return std::make_pair(4, hand);
    else if (twoPairs(hand)) return std::make_pair(3, hand);
    else if (onePair(hand)) return std::make_pair(2, hand);
    else if (high(hand)) return std::make_pair(1, hand);
    else return std::make_pair(0, hand);
}

struct Hand
{
    int bid;
    std::vector<char> hand;

    Hand(int _bid, const std::vector<char> _hand) : bid(_bid), hand(_hand) {}

    bool operator < (const Hand& otherHand) const {
        int handRank = rankHand(hand).first;
        int otherHandRank = rankHand(otherHand.hand).first;
        
        if (handRank != otherHandRank) return handRank < otherHandRank;
        else {
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == otherHand.hand[i]) continue;
                else return hand[i] < otherHand.hand[i];
            }
            return false;
        }
    }
};

std::string solve(char** argv) {
    std::vector<std::string> input = getInput(argv[1]);

    int ans = 0;
    
    std::map<char, char> getCharReplacement;
    std::vector<char> chars = {'A','K','Q','J','T'};
    for (int i = 0; i < chars.size(); i++) {
        getCharReplacement[chars[i]] = (char) '9' + (chars.size() - i);
    }

    std::vector<Hand> hands;

    for (int i = 0; i < input.size(); i++) {
        std::vector<char> hand;
        double bid = 0;

        bool hitSpace = false;
        for (int j = 0; j < input[i].size(); j++) {
            char curr = input[i][j];

            if (curr == ' ') {
                hitSpace = true;
                continue;
            } else if (!hitSpace && std::isdigit(curr)) {
                hand.push_back(curr);
            } else if (!hitSpace && !std::isdigit(curr)) {
                hand.push_back(getCharReplacement[curr]);
            } else if (hitSpace && std::isdigit(curr)) {
                bid = bid * 10 + curr - '0';
            }
        }

        Hand newHand = Hand(bid, hand);
        hands.push_back(newHand);
    }

    std::sort(hands.begin(), hands.end());

    for (int i = 0; i < hands.size(); i++) {
        Hand curr = hands[i];
        ans += curr.bid * (i+1);
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

