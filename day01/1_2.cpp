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
    std::string line;
    int result = 0;
    while (std::getline(file, line)){

    } 
    cout << result << endl;

    return 0;
}