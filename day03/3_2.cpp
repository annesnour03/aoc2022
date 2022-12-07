#include "../helper.h"
using namespace std;

void make_unique(std::string &s) {
    sort(s.begin(), s.end());
    unique(s.begin(), s.end());
}

int solve(std::vector<string> input) {
    int res = 0;
    for (int i = 0; i < input.size(); i += 3) {
        string overlap = "";
        string first = input[i];
        string second = input[i + 1];
        string third = input[i + 2];
        make_unique(first);
        make_unique(second);
        make_unique(third);
        set_intersection(first.begin(), first.end(), second.begin(), second.end(), back_inserter(overlap));
        set_intersection(overlap.begin(), overlap.end(), third.begin(), third.end(), back_inserter(overlap));
         if (overlap.back() >= 'a')
            res += (overlap.back() - 'a' + 1);
        else
            res += (overlap.back() - '&');
    }
    return res;
}
int main(int argc, char *argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<string> parsed_data;
    while (std::getline(file, line)) {
        parsed_data.push_back(line);
    }
    cout << solve(parsed_data) << endl;

    return 0;
}