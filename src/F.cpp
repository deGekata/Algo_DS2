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

std::string StrFromPrefix(std::vector<int>& pref) {
    std::string ans;
    ans.resize(pref.size());
    std::vector<bool> used_symbols('z' - 'a' + 1);

    int n = static_cast<int>(pref.size());
    for (int it = 0; it < n; ++it) {

        if (pref[it] != 0) {
            ans[it] = ans[pref[it] - 1];
        } else {

            used_symbols.assign(used_symbols.size(), false);
            if (it == 0) {
                ans[it] = 'a';
                continue;
            }

            if (it == 1) {
                ans[it] = 'b';
                continue;
            }

            int cur_ind = it;

            do {
                used_symbols[ans[pref[cur_ind - 1]] - 'a'] = true;
                cur_ind = pref[cur_ind - 1];
            } while (cur_ind > 0);

            for (size_t free_symbol = 0; free_symbol < used_symbols.size(); ++free_symbol) {
                if (!used_symbols[free_symbol]) {
                    ans[it] = static_cast<char>(static_cast<size_t>(97) + free_symbol);
                    break;
                }
            }
        }
    }

    return ans;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> zetta(n, 0);
    std::vector<int> pref(n, 0);

    for (int it = 0; it < n; ++it) {
        std::cin >> zetta[it];
    }

    for (int it = 1; it < n; ++it) {
        if (zetta[it]) {
            for (int jit = zetta[it] - 1; jit >= 0 && !(pref[it + jit]); --jit) {
                pref[it + jit] = jit + 1;
            }
        }
    }
    
    std::string st = StrFromPrefix(pref);
    std::cout << st;
    return 0;
}
