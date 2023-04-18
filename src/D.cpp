
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cinttypes>

void ZFunc(std::string arr, size_t text_len) {
    size_t arr_len = static_cast<int>(arr.size());
    std::vector<size_t> z(arr_len, 0);

    size_t it = 1;
    size_t lft = 0;
    size_t rht = 0;
    for (; it < arr_len; ++it) {
        if (it <= rht) {
            z[it] = std::min ((rht - it) + 1, z[it - lft]);
        }

        while ((it + z[it] < arr_len) && (arr[z[it]] == arr[it + z[it]])) {
            ++z[it];
        }

        if ((it + z[it] - 1) > rht) {
            lft = it;
            rht = it + z[it] - 1;
        }
    }

    // for (auto& v: z) {
    //     std::cout << v << " ";
    // }
    // std::cout << "\n";

    rht = 0;
    lft = text_len + 1ULL;
    // bool flag = false;

    std::vector<std::string> ans;

    // операция по спасению осла в первую очередь!!! :)
    for (size_t it = text_len + 1ULL; it < arr_len; ++it) {
        if (!z[it]){
            if (it > rht) {
                std::cout << "Yes\n";
                return;
            }

        } else if (z[it] + it > rht + 1) {
            rht = z[it] + it - 1;

            if (lft != it) {
                ans.push_back(arr.substr(lft, it - lft));
            }

            lft = it;
        }
    }

    // фахаххахаахахаххахх строка длиной 1 ахахаххахаа почему плакац хочеца
    // if (!flag) {
    // }
    std::cout << "No\n";
    ans.push_back(arr.substr(lft));

    for (auto& v: ans) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

int main() {
    std::string pattern;
    std::string txt;
    std::cin >> txt >> pattern;

    ZFunc(txt + "#" + pattern, txt.length());

    return 0;
}
