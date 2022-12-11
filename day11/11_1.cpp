#include "../helper.h"
struct Monkey {
    int id;

    std::vector<int> items;
    char operation;
    int amount;
    int test_amount;

    int false_monkey;
    int true_monkey;

    bool square = false;
    int inspected = 0;
};

void throw_item(Monkey& x, Monkey& y) {
    int first_item = x.items[0];
    y.items.push_back(first_item);
    x.items.erase(x.items.begin());
    x.items.shrink_to_fit();
}

void get_new_score(Monkey& m) {
    if (m.operation == '*') {
        int mult = 0;
        if (m.square)
            mult = m.items[0];
        else
            mult = m.amount;
        m.items[0] = (m.items[0] * mult) / 3;
    } else {
        m.items[0] = (m.items[0] + m.amount) / 3;
    }
}

bool test_throw(Monkey& m) {
    return m.items[0] % m.test_amount == 0;
}

int solve(std::vector<Monkey> input) {
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < input.size(); i++) {
            Monkey* m = &input[i];
            const int initial = m->items.size();
            for (int i = 0; i < initial; i++) {
                get_new_score(*m);
                m->inspected++;
                if (test_throw(*m)) {
                    throw_item(*m, input[m->true_monkey]);
                } else {
                    throw_item(*m, input[m->false_monkey]);
                }
            }
        }
    }
    std::sort(input.begin(), input.end(), [](Monkey a, Monkey b) {
        return a.inspected > b.inspected;
    });
    return input[0].inspected * input[1].inspected;
}

int main(int argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::string> parsed_data;
    int line_idx = 0;
    Monkey m;
    std::vector<Monkey> monkeys;
    int absolute = 0;
    while (std::getline(file, line)) {
        if (!line_idx && absolute) {
            monkeys.push_back(m);
            Monkey m;
        }
        switch (line_idx) {
            case 0:
                m.id = std::stoi(&split(line, ' ')[1][0]);
                break;
            case 1: {
                std::vector<std::string> cut = split(line, ' ');
                std::string v2 = join(std::vector<std::string>(cut.begin() + 4, cut.end()), " ");
                v2.erase(std::remove(v2.begin(), v2.end(), ','), v2.end());
                std::stringstream iss(v2);
                std::vector<int> my((std::istream_iterator<int>(iss)), (std::istream_iterator<int>()));
                m.items = my;
            } break;

            case 2: {
                char cut = split(line, ' ')[6][0];
                m.operation = cut;
                std::string amount = split(line, ' ')[7];
                if (amount != "old")
                    m.amount = std::stoi(amount);
                else {
                    m.amount = -1;
                    m.square = true;
                }
            } break;
            case 3: {
                std::string cut = split(line, ' ')[5];
                m.test_amount = std::stoi(cut);
            } break;
            case 4: {
                std::string cut = split(line, ' ')[9];
                m.true_monkey = std::stoi(cut);

            } break;
            case 5: {
                std::string cut = split(line, ' ')[9];
                m.false_monkey = std::stoi(cut);

            } break;

            default:
                break;
        }

        parsed_data.push_back(line);
        line_idx = ++line_idx % 7;
        absolute++;
    }
    monkeys.push_back(m);

    cout << solve(monkeys) << endl;
    return 0;
}