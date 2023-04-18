#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

using INT = int;
using UINT = unsigned int;
std::vector<INT> PrefixFunc(std::string target) {
    std::vector<INT> answer(target.length());

    for (size_t it = 1; it < target.length(); ++it) {
        INT cur_val = answer[it - 1];

        while (cur_val > 0 && target[cur_val] != target[it]) {
            cur_val = answer[cur_val - 1];
        }

        if (target[it] == target[cur_val]) {
            ++cur_val;
        }

        answer[it] = cur_val;
    }

    return answer;
}

int main() {
    std::string pattern;
    std::string str;
    std::cin >> str >> pattern;

    std::string buff(pattern + "#" + str);
    std::vector<INT> answer(PrefixFunc(buff));

    for (size_t ind = pattern.length() + 1; ind < answer.size(); ++ind) {

        if (answer[ind] == static_cast<int>(pattern.length())) {
            std::cout << ind - 2 * pattern.length() << "\n";
        }
    }

    return 0;
}
