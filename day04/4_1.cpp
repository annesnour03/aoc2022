#include "../helper.h"

struct Range {
    int start;
    int end;
    Range(int start, int end) {
        this->start = start;
        this->end = end;
    }

    friend std::ostream &operator<<(std::ostream &os, const Range value) {
        os << value.start << "-" << value.end;
        return os;
    }
};
int solve(std::vector<Range> input) {
    int res = 0;
    for (int i = 0; i < input.size(); i += 2) {
        Range first = input[i];
        Range second = input[i + 1];
        cout << first << " and " << second << endl;
        if (first.start >= second.start && first.end <= second.end)
            res++;
        else if (second.start >= first.start && second.end <= first.end)
            res++;
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
    std::vector<Range> parsed_data;
    while (std::getline(file, line)) {
        std::vector<std::string> r = split(line, ',');
        for (auto var : r) {
            std::vector<std::string> b = split(var, '-');
            parsed_data.push_back(Range(stoi(b[0]), stoi(b[1])));
        }
    }
    cout << solve(parsed_data) << endl;

    return 0;
}