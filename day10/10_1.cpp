#include "../helper.h"

struct Instruction {
    std::string ins;
    int add;
};
int solve(std::vector<Instruction> input) {
    int cycle = 1;
    int X = 1;
    std::vector<int> log;
    for (Instruction line : input) {
        if (line.ins == "noop") {
            log.push_back(X);
            cycle++;
            continue;
        } else if (line.ins == "addx") {
            log.push_back(X);
            log.push_back(X);
            cycle += 2;
            X += line.add;
        }
    }

    int res = 0;
    for (int time : {20, 60, 100, 140, 180, 220}) {
        res += log[time - 1] * time;
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
    std::vector<Instruction> parsed_data;
    while (std::getline(file, line)) {
        std::vector<std::string> a = split(line, ' ');
        if (a.size() == 1)
            parsed_data.push_back({a[0], 0});
        else
            parsed_data.push_back({a[0], std::stoi(a[1])});
    }
    cout << solve(parsed_data) << endl;
    return 0;
}