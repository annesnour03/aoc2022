#include "../helper.h"
int get_score_up(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    int c = 0;
    for (int y = i - 1; y >= 0; y--) {
        if (input[y][j] >= current) {
            c++;
            break;
        }
        c++;
    }
    return c;
}
int get_score_down(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    int c = 0;
    for (int y = i + 1; y < input.size(); y++) {
        if (input[y][j] >= current) {
            c++;
            break;
        }
        c++;
    }
    return c;
}
int get_score_right(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    int c = 0;
    for (int x = j + 1; x < input[0].size(); x++) {
        if (input[i][x] >= current) {
            c++;
            break;
        }
        c++;
    }
    return c;
}
int get_score_left(std::vector<std::vector<int>>& input, int i, int j) {
    int current = input[i][j];
    int c = 0;
    for (int x = j - 1; x >= 0; x--) {
        if (input[i][x] >= current) {
            c++;
            break;
        }
        c++;
    }
    return c;
}

int get_senic_score(std::vector<std::vector<int>>& input, int i, int j) {
    int score = 1;
    score *= get_score_left(input, i, j);
    score *= get_score_right(input, i, j);
    score *= get_score_up(input, i, j);
    score *= get_score_down(input, i, j);

    return score;
}

int solve(std::vector<std::vector<int>> input) {
    int res = 0;
    const int height = input.size();
    const int width = input[0].size();
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            int val = get_senic_score(input, i, j);
            if (val > res)
                res = val;
        }
    }
    return res;
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