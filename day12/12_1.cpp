#include <deque>

#include "../helper.h"
struct Cell {
    int x, y, distance = 0;

    bool isValid(std::vector<std::string>& mtx, int new_x, int new_y, const int width, const int heigth) const {
        bool inbound = (new_x >= 0 && new_x < width) && (new_y >= 0 && new_y < heigth);
        if (!inbound)
            return false;
        if (mtx[y][x] == 'S')
            return true;
        bool moving_up = (mtx[new_y][new_x] - mtx[y][x] <= 1);
        if (mtx[new_y][new_x] == 'E')
            return inbound && moving_up && (('z' - mtx[y][x] == 0));

        return inbound && moving_up;
    }
};
int solve(std::vector<std::string> input) {
    int res = 0;
    Cell source;
    const int width = input[0].size();
    const int heigth = input.size();

    std::vector<std::vector<bool>> visited;
    for (int i = 0; i < heigth; i++) {
        visited.push_back({});
        for (int j = 0; j < width; j++) {
            visited[i].push_back(false);
            // Finding source
            if (input[i][j] == 'S') {
                source = {j,i};
                visited[i].push_back(true);
            }
        }
    }
    int row[] = {1, -1, 0, 0};
    int col[] = {0, 0, 1, -1};

    std::deque<Cell> q;
    q.push_back(source);
    while (!q.empty()) {
        Cell current = q.front();
        q.pop_front();
        if (input[current.y][current.x] == 'E')
            return current.distance;
        for (int j = 0; j < 4; j++) {
            int new_x = current.x + col[j];
            int new_y = current.y + row[j];
            if (current.isValid(input, new_x, new_y, width, heigth) && !visited[new_y][new_x]) {
                visited[new_y][new_x] = true;
                q.push_back({new_x, new_y, current.distance + 1});
            }
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
    std::vector<std::string> parsed_data;
    while (std::getline(file, line)) {
        parsed_data.push_back(line);
    }
    cout << solve(parsed_data) << endl;
    return 0;
}