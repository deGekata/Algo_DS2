
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> PrefixFunc(std::string target) {
    std::vector<int> answer(target.length());

    for (size_t it = 1; it < target.length(); ++it) {
        int cur_val = answer[it - 1];

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
    int n = 0;
    std::cin >> n;

    std::string result;
    std::string current;
    std::string buff;

    std::cin >> result;
    std::vector<int> pref;
    for (int it = 0; it < n - 1; ++it) {
        std::cin >> current;
        int delta = static_cast<int>(result.length()) - static_cast<int>(current.length());

        buff = current + "#" + result.substr(std::max(0, delta), result.length());
        pref = PrefixFunc(buff);
        size_t max_pref = pref[pref.size() - 1];

        if (max_pref <= current.length()) {
            result += current.substr(max_pref, current.length() - max_pref);
        }
    }

    std::cout << result;

    return 0;
}
