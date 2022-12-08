#include "../helper.h"
typedef std::stack<char> container_stack;
struct Ship {
   public:
    std::vector<container_stack> stacks;

    Ship(const int width) {
        stacks.resize(width);
    }
};

struct Instruction {
    int amount, from, to;
};

void get_column(std::vector<std::vector<char>> crates, container_stack *out, int column) {
    container_stack tmp_stack;
    for (auto row : crates) {
        if (row[column] != ' ')
            tmp_stack.push(row[column]);
    }

    // Reverse the stack
    while (tmp_stack.size()) {
        const char top = tmp_stack.top();
        tmp_stack.pop();
        out->push(top);
    }
}

std::vector<char> *parse_line_input(std::string s) {
    std::vector<char> *out = new std::vector<char>;
    for (int i = 0; i < s.size(); i += 4) {
        if (s[i + 1] == '1') {
            delete out;
            return nullptr;
        }
        out->push_back(s[i + 1]);
    }
    return out;
}

void solve(Ship *sh, std::vector<Instruction> instructions) {
    int res = 0;
    for (auto instruction : instructions) {
        std::vector<char> tmp;
        for (int i = 0; i < instruction.amount; i++) {
            const char top = sh->stacks[instruction.from - 1].top();
            sh->stacks[instruction.from - 1].pop();
            tmp.push_back(top);
        }
        std::reverse(tmp.begin(), tmp.end());
        for (auto crate : tmp) {
            sh->stacks[instruction.to - 1].push(crate);
        }
    }
    for (auto st : sh->stacks) {
        cout << st.top();
    }
    cout << endl;
}

// Persistent on not altering the input data, thats why this is so long.
int main(int argc, char *argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::vector<char>> parsed_data;
    while (std::getline(file, line)) {
        std::vector<char> *a = parse_line_input(line);
        if (!a)
            break;
        parsed_data.push_back(a[0]);
        delete a;
    }
    const int width = (line.length() + 1) / 4;
    std::vector<Instruction> instructions;

    // Read out instructions
    while (std::getline(file, line)) {
        if (line.length() == 0)
            continue;
        std::vector<std::string> a = split(line, ' ');
        Instruction ins = {stoi(a[1]), stoi(a[3]), stoi(a[5])};
        instructions.push_back(ins);
    }
    Ship *sh = new Ship(width);
    for (int i = 0; i < width; i++) {
        get_column(parsed_data, &sh->stacks[i], i);
    }
    solve(sh, instructions);
    delete sh;

    return 0;
}