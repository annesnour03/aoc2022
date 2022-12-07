#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
using std::cout;
using std::endl;

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}