#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
bool isEmptyLine(std::string line) {
    return line.length() == 0;
}
int choice_to_score(int choice) {
    return choice - 'A' + 1;
}
int need_draw(int my_choice, int opponent) {
    if (my_choice == 'B') {
        return opponent;
    }
    return 0;
}

int need_win(int my_choice, int opponent) {
    if (my_choice == 'C') {
        int next = (opponent + 1) % 'D';
        return next ? next : (int)'A';
    }
    return 0;
}
int need_loose(int my_choice, int opponent) {
    if (my_choice == 'A') {
        if (opponent == 'A')
            return 'C';
        if (opponent == 'B')
            return 'A';
        return 'B';
    }
    return 0;
}

int solve(std::vector<std::tuple<char, char>> input) {
    int opponent, my_choice, playback, res = 0;
    for (auto &line : input) {
        opponent = get<0>(line);
        my_choice = get<1>(line);
        if ((playback = need_draw(my_choice, opponent)))
            res = res + 3 + choice_to_score(playback);
        else if ((playback = need_win(my_choice, opponent))) {
            res = res + 6 + choice_to_score(playback);
        } else if ((playback = need_loose(my_choice, opponent))) {
            res = res + 0 + choice_to_score(playback);
        }
    }

    return res;
}
int main(int argc, char *argv[]) {
    std::string input = "2_1.input";
    // In case we need to work with sample input.
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    int result = 0;
    std::vector<std::tuple<char, char>> parsed_data;
    while (std::getline(file, line)) {
        const int difference = (int)'Z' - (int)'C';
        std::vector<std::string> a = split(line, ' ');
        std::tuple<char, char> b = {a[0][0],
                                    (int)a[1][0] - difference};
        parsed_data.push_back(b);
    }
    cout << solve(parsed_data) << endl;

    return 0;
}