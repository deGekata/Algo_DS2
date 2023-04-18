
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cinttypes>

void ZFunc(std::vector<size_t> arr, size_t text_len) {
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

    for (size_t jit = text_len + 1; jit < arr_len; ++jit) {
        
        if ((jit % 2) && ((2 * z[jit]) >= (2 * text_len - jit + 1))) {
            std::cout << text_len - ((2 * text_len - jit) + 1) / 2 << " ";
        }
    }

    std::cout << text_len;
}

int main() {
    size_t cubes_cnt = 0;
    size_t color_cnt = 0;
    std::cin >> cubes_cnt >> color_cnt;
    std::vector<size_t> colors(cubes_cnt * 2 + 1, 0);
    
    for (size_t it = 0; it < cubes_cnt; ++it) {
        std::cin >> colors[it];
        colors[2 * cubes_cnt - it] = colors[it];
    }

    colors[cubes_cnt] = color_cnt + 1;

    ZFunc(colors, cubes_cnt);

    return 0;
}
