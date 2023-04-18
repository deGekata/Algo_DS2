#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <random>
#include <unordered_set>

 
struct Hash {
    const static int32_t kMod  = 1000000123;
    const static int32_t kBase = 507;
    static std::vector<int32_t> pow1;      
    static std::vector<uint64_t> pow2; 
 

    std::vector<int32_t> pref1;
    std::vector<uint64_t> pref2;
 
    explicit Hash(const std::string& st)
        : pref1(st.size()+1ull, 0)
        , pref2(st.size()+1ull, 0)
    {
        for (; pow1.size() <= st.length(); pow1.push_back(static_cast<int>((static_cast<int64_t>(pow1.back()) * kBase) % kMod)), pow2.push_back(pow2.back() * kBase)) {
        }

        for (size_t pos = 0; pos < st.size(); ++pos) {
            pref1[pos+1] = static_cast<int>((pref1[pos] + 1LL * st[pos] * pow1[pos]) % kMod);
            pref2[pos+1] = pref2[pos] + st[pos] * pow2[pos];
        }
    }
 
    inline std::pair<int, uint64_t> HashSlice(const int pos, const int len, const int max_pow = 0) const {
        int hash1 = pref1[pos+len] - pref1[pos];
        uint64_t hash2 = pref2[pos+len] - pref2[pos];

        if (hash1 < 0)  {
            hash1 += kMod;
        }

        hash1 = static_cast<int>(static_cast<int64_t>(hash1) * pow1[max_pow-(pos+len-1)] % kMod);
        hash2 *= pow2[max_pow-(pos+len-1)];

        return {hash1, hash2};
    }
};

std::vector<int> Hash::pow1{1};
std::vector<uint64_t> Hash::pow2{1};
 

// add hash for unordered_set
namespace std {
    template <>
    struct hash<std::pair<int32_t, uint64_t>> {
        size_t operator()(const std::pair<int32_t, uint64_t> &v) const {
            std::hash<int32_t> pair_first;
            std::hash<uint64_t> pair_second;
            return pair_first(v.first) + 31 * pair_second(v.second);
        }
    };
}

int main() {

    std::string pattern;
    std::string text;
    std::cin >> pattern >> text;
    if (pattern.length() > text.length()) {
        std::cout << 0;
        return 0;
    }

    auto pattern_len = pattern.length();
    pattern = pattern + pattern;
 

    int max_pow = static_cast<int>(std::max(text.size(), pattern.size()));

    Hash hash_pattern(pattern);
    Hash hash_text(text);
 
    std::unordered_set<std::pair<int, uint64_t>> st;
    // std::vector<std::pair<int, uint64_t>> hashes;

    for (size_t it = 0; it < pattern_len; ++it) {
        // std::cout << "inserted" << hash_pattern.Hash_slice(it, it + pattern_len, max_pow).first << " " << hash_pattern.Hash_slice(it, it + pattern_len, max_pow).second << "\n";
        st.insert(hash_pattern.HashSlice(static_cast<int>(it), static_cast<int>(pattern_len), max_pow));
    }

    // for (int i = 0; i  < (int)b.size(); ++i) {
    //     hashes.push_back(hash_b(i, b.size(), mxPow));
    // }
    // std::sort(hashes.begin(), hashes.end());
 
    int answ = 0;
    for (size_t it = 0; it < (text.size() + 1 - pattern_len); ++it) {
        // std::cout << "searching" << hash_text.Hash_slice(it, pattern_len, max_pow).first << " " << hash_text.Hash_slice(it, pattern_len, max_pow).second << "\n";
        // if (st.find(hash_text.Hash_slice(it, pattern_len, max_pow)) != st.end()) {
        //     // std::cout << "yes";
        // }
        answ += (st.find(hash_text.HashSlice(static_cast<int>(it), static_cast<int>(pattern_len), max_pow)) != st.end()) ? 1 : 0;
    }

    std::cout << answ;
 
    return 0;
}