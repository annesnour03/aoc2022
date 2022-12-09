#include "../helper.h"
bool valid_up(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    for (int y = 0; y < i; y++) {
        if (input[y][j] >= current)
            return false;
    }
    return true;
}
bool valid_down(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    for (int y = i  + 1; y < input.size(); y++) {
        if (input[y][j] >= current)
            return false;
    }
    return true;
}
bool valid_right(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    for (int x = j + 1; x < input[0].size(); x++) {
        if (input[i][x] >= current)
            return false;
    }
    return true;
}
bool valid_left(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    for (int x = 0; x < j; x++) {
        if (input[i][x] >= current)
            return false;
    }
    return true;
}

int solve(std::vector<std::vector<int>> input) {
    int res = 0;
    const int height = input.size();
    const int width = input[0].size();
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (valid_left(input, i, j) || valid_right(input, i, j) || valid_up(input, i, j) || valid_down(input, i, j))
                res++;
        }
    }
    return res + 2 * height + 2 * width - 4;
}
int main(int argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::vector<int>> parsed_data;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            row.push_back(char_2_int(c));
        }
        parsed_data.push_back(row);
    }
    cout << solve(parsed_data) << endl;
    return 0;
}