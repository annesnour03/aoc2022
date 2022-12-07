#include "../helper.h"
using namespace std;

void make_unique(std::string &s) {
    sort(s.begin(), s.end());
    unique(s.begin(), s.end());
}

int solve(std::vector<string> input) {
    int res = 0;
    for (auto sack : input) {
        string i;
        const int half = sack.size() / 2;
        string first = sack.substr(0, half);
        string second = sack.substr(half, sack.size());
        make_unique(first);
        make_unique(second);
        set_intersection(first.begin(), first.end(), second.begin(), second.end(), back_inserter(i));
        if (i[0] >= 'a')
            res += (i[0] - 'a' + 1);
        else
            res += (i[0] - '&');
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
    int result = 0;
    std::vector<string> parsed_data;
    while (std::getline(file, line)) {
        parsed_data.push_back(line);
    }
    cout << solve(parsed_data) << endl;

    return 0;
}