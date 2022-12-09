#include <map>
#include <ranges>

#include "../helper.h"

struct Position {
    int x, y;

    Position operator+(const Position other) const {
        return {other.x + this->x, other.y + this->y};
    }

    Position operator-(const Position other) const {
        return {this->x - other.x, this->y - other.y};
    }

    bool const operator<(const Position &other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Position value) {
        os << "(" << value.x << ", " << value.y << ")";
        return os;
    }

    int dist_to(const Position &other) const {
        return sqrt(pow(abs(this->x - other.x), 2) +
                    pow(abs(this->y - other.y), 2));
    }
    bool same_row_or_column(const Position &other) const {
        return (other.x == this->x || other.y == this->y);
    }

    bool is_nearby(const Position &other) { return this->dist_to(other) <= 1; }
};
struct Instruction {
    char d;
    int amount;
    friend std::ostream &operator<<(std::ostream &os, const Instruction value) {
        os << value.d << " " << value.amount;
        return os;
    }
};
Position get_new_pos(char c, Position p) {
    Position add;
    switch (c) {
        case 'R':
            add = {1, 0};
            break;
        case 'L':
            add = {-1, 0};
            break;
        case 'U':
            add = {0, 1};
            break;
        case 'D':
            add = {0, -1};
            break;
        default:
            add = {0, 0};
            break;
    }
    return p + add;
}

int solve(std::vector<Instruction> input) {
    int res = 0;
    Position head = {0, 0};
    Position tail = {0, 0};

    std::map<Position, int> locations;
    locations[tail] = 1;
    // We start at 0,0
    for (int i = 0; i < input.size(); i++) {
        Instruction current = input[i];
        for (int j = 0; j < current.amount; j++) {
            // Simply move the head
            head = get_new_pos(current.d, head);
            // We dont have to move anything.
            if (head.is_nearby(tail)) continue;
            if (!head.same_row_or_column(tail)) {
                Position q = head - tail;
                Position add = {-1, -1};
                if (q.x > 0)
                    add.x = 1;

                if (q.y > 0)
                    add.y = 1;
                tail = tail + add;
            } else {
                tail = get_new_pos(current.d, tail);
            }

            locations[tail]++;
        }
    }
    // Retrieve all keys from map;
    std::vector<Position> itemKeys;

    for (const auto &[key, _] : locations) {
        itemKeys.push_back(key);
    }
    return itemKeys.size();
}
int main(int argc, char *argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<Instruction> parsed_data;
    while (std::getline(file, line)) {
        auto a = split(line, ' ');
        parsed_data.push_back({*(a[0].c_str()), std::stoi(a[1])});
    }
    cout << solve(parsed_data) << endl;
    return 0;
}