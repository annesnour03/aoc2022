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
int is_draw(int my_choice, int opponent) {
    return my_choice == opponent;
}
bool i_won(int my_choice, int opponent) {
    if ((char)opponent == 'C' && (char)my_choice == 'A')
        return true;
    if ((char)opponent == 'A' && (char)my_choice == 'C')
        return false;
    return my_choice > opponent;
}

int solve(std::vector<std::tuple<char, char>> input) {
    int opponent, my_choice, res = 0;
    for (auto &line : input) {
        opponent = get<0>(line);
        my_choice = get<1>(line);

        if (is_draw(my_choice, opponent))
            res = res + 3 + choice_to_score(my_choice);
        else if (i_won(my_choice, opponent)) {
            res = res + 6 + choice_to_score(my_choice);
        } else {
            res = res + 0 + choice_to_score(my_choice);
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