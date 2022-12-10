#include "../helper.h"

struct Instruction {
    std::string ins;
    int add;
};

bool is_close(int X, int position) {
    position = position % 40;
    return abs(X - position) <= 1;
}

void draw_pixel(std::vector<std::vector<char>>& crt, int c) {
    crt[c / 40][c % 40] = '#';
}

void solve(std::vector<Instruction> input) {
    std::vector<std::vector<char>> crt;
    for (int i = 0; i < 6; i++) {
        crt.push_back({});
        for (int j = 0; j < 40; j++) {
            crt[i].push_back('.');
        }
    }
    int cycle = 1;
    int X = 1;
    for (Instruction line : input) {
        if (line.ins == "noop") {
            if (is_close(X, cycle - 1))
                draw_pixel(crt, cycle - 1);
            cycle++;
            continue;
        } else if (line.ins == "addx") {
            if (is_close(X, cycle - 1))
                draw_pixel(crt, cycle - 1);
            cycle++;
            if (is_close(X, cycle - 1))
                draw_pixel(crt, cycle - 1);
            cycle++;
            X += line.add;
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            cout << crt[i][j];
        }
        cout << endl;
    }
}
int main(int argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<Instruction> parsed_data;
    while (std::getline(file, line)) {
        std::vector<std::string> a = split(line, ' ');
        if (a.size() == 1)
            parsed_data.push_back({a[0], 0});
        else
            parsed_data.push_back({a[0], std::stoi(a[1])});
    }
    solve(parsed_data);
    return 0;
}
