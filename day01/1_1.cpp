#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

bool isEmptyLine(std::string line) {
    return line.length() == 0;
}

int main(int argc, char* argv[]) {
    std::string input = "01.input";
    // In case we need to work with sample input.
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::vector<int> carrys(1);
    int i = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (isEmptyLine(line)) {
            ++i;
            carrys.push_back(0);
            continue;
        }
        int val = std::stoi(line);
        carrys.at(i) = carrys[i] + val;
    }
    std::sort(carrys.rbegin(), carrys.rend());
    cout << carrys[0] << endl;

    return 0;
}