
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

inline uint64_t CharNormalize(char& c) {
    return static_cast<uint64_t>(c - 'a' + 1);
}

// here we need some guarantees:
// there are <= 32 different chars and also lenght <= 10
// We are just packing characters inside uint64_t and map hash x -> x
struct PackedStr {
    uint64_t len = 0;
    uint64_t straight = 0;
    uint64_t reversed = 0;

    explicit PackedStr(std::string& st) 
        : len(st.size())
    {
        for (size_t cur_len = 0; cur_len < len; ++cur_len) {
            straight = (straight << 5) ^ static_cast<uint64_t>(CharNormalize(st[cur_len]));
            reversed = (reversed << 5) ^ static_cast<uint64_t>(CharNormalize(st[len - cur_len - 1ULL]));
        }
    }

    uint64_t PrefSlice(int begin, int end) {
        // ахахха сейчас бы из len begin вычитать аххахахахаххахах..... 1000-7
        return (straight >> ((len - end) * 5)) & ((1ULL << (5 * (end - begin))) - 1);
    }

    uint64_t RevSlice(int begin, int end) {
        return (reversed >> ((len - end) * 5)) & ((1ULL << (5 * (end - begin))) - 1);
    }

};

namespace std {
    template <>
    struct hash<std::pair<int32_t, int32_t>> {
        size_t operator()(const std::pair<int32_t, uint64_t> &v) const {
            return (static_cast<uint64_t>(v.second) << 32) + static_cast<uint64_t>(v.first);
        }
    };
}



int main() {
    std::string buff;
    std::vector<int32_t> strings_len;
    std::vector<PackedStr> packed;
    std::unordered_map<uint64_t, int32_t> entries;
    std::unordered_set<std::pair<int32_t, int32_t>> answer;
    int st_cnt = 0;
    std::cin >> st_cnt;

    for (int it = 0; it < st_cnt; ++it) {
        std::string tmp;
        std::cin >> tmp;

        strings_len.push_back(static_cast<int32_t>(tmp.size()));
        packed.emplace_back(tmp);
        entries.insert({packed[it].straight, it});
    }

    for (int32_t it = 0; it < st_cnt; ++it) {
        for (int32_t targ_l = 1; targ_l < strings_len[it] + 1; ++targ_l) {
            // std::cout << "cur " << it << " conc_size" << targ_l << "\n";
            int conc_len = targ_l + strings_len[it];

            if (packed[it].RevSlice(0, strings_len[it] - (conc_len - conc_len / 2)) == packed[it].PrefSlice(targ_l, conc_len / 2)) {
                auto res = entries.find(packed[it].RevSlice(strings_len[it] - targ_l, strings_len[it]));   
                if (res != entries.end()) {
                    if (it != res->second) {
                        answer.insert({it + 1, res->second + 1});
                        // std::cout << it + 1 << " " << res->second + 1 << "\n";
                    }
                }
            }

            if (packed[it].PrefSlice(0, strings_len[it] - (conc_len - conc_len / 2)) == packed[it].RevSlice(targ_l, conc_len / 2)) {
                auto res = entries.find(packed[it].RevSlice(0, targ_l));   
                if (res != entries.end()) {
                    if (it != res->second) {
                        answer.insert({res->second + 1, it + 1});
                        // std::cout << res->second + 1 << " " << it + 1 << "\n";
                    }
                }
            }

        }
    }

    std::cout << answer.size() << "\n";

    for (auto& v: answer) {
        std::cout << v.first << " " << v.second << "\n";
    }

    return 0;
}
