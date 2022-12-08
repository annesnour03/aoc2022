#include "../helper.h"
void make_unique(std::string s) {
    sort(s.begin(), s.end());
    unique(s.begin(), s.end());
}
int solve(std::string input) {
    const int size = 14;
    for (int i = 0; i < input.size(); i++) {
        std::string sub = input.substr(i, size);
        sub = unique(sub);
        if (sub.length() == size)
            return i + size;
    }
}
int main(int argc, char *argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::string parsed_data;
    while (std::getline(file, line)) {
        parsed_data = line;
    }
    cout << solve(parsed_data) << endl;

    return 0;
}