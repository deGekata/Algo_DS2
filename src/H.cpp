#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <string>
 
typedef unsigned long long ull;
 
// Генерация случайного основания хэширования на отрезке (before, after):
int gen_base(const int before, const int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    int base = std::uniform_int_distribution<int>(before+1, after)(mt_rand);
    return base % 2 == 0 ? base-1 : base;
}
 
struct Hash {
    // -------- Статические переменные класса --------
    static const int kMod = (int)1e9+123; // простой модуль полиномиального хэширования
    static std::vector<int> pow1;        // степени основания base по модулю mod
    static std::vector<ull> pow2;        // степени основания base по модулю 2^64
    static int kBase;                     // основание base
 
    // --------- Статические функции класса ---------
    static inline int diff(int a, int b) { // разность a и b по модуль mod (Предполагается: 0 <= a < mod, 0 <= b < mod)
        return (a -= b) < 0 ? a + kMod : a;
    }
 
    // -------------- Переменные класса -------------
    std::vector<int> pref1; // Полиномиальный хэш на префиксе по модулю mod
    std::vector<ull> pref2; // Полиномиальный хэш на префиксе по модулю 2^64
 
    // Конструктор от строки:
    Hash(const std::string& s)
        : pref1(s.size()+1u, 0)
        , pref2(s.size()+1u, 0)
    {
        assert(kBase < kMod);
        const int n = s.size(); // Досчитываем необходимые степени основания по модулям хэширования
        while ((int)pow1.size() <= n) {
            pow1.push_back(1LL * pow1.back() * kBase % kMod);
            pow2.push_back(pow2.back() * kBase);
        }
        for (int i = 0; i < n; ++i) { // Заполняем массив полиномиальных хэшей на префиксе
            assert(kBase > s[i]);
            pref1[i+1] = (pref1[i] + 1LL * s[i] * pow1[i]) % kMod;
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
    }
 
    // Полиномиальный хэш подпоследовательности [pos, pos+len)
    // Если mxPow != 0, то происходит домножение значения до старшей степени base ^ mxPow
    inline std::pair<int, ull> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = pref1[pos+len] - pref1[pos];
        ull hash2 = pref2[pos+len] - pref2[pos];
        if (hash1 < 0) hash1 += kMod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow-(pos+len-1)] % kMod;
            hash2 *= pow2[mxPow-(pos+len-1)];
        }
        return std::make_pair(hash1, hash2);
    }
};
 
// Инициализация статических объектов класса PolyHash:
int Hash::kBase((int)1e9+7);    
std::vector<int> Hash::pow1{1};
std::vector<ull> Hash::pow2{1};
 
int main() {
    // Чтение данных:
    char buf[1+100000];
    scanf("%100000s", buf);
    std::string b(buf);
    scanf("%100000s", buf);
    std::string a(buf);
 
    // Вычисление максимальной степени:
    const int mxPow = std::max((int)a.size(), (int)b.size() * 2);
 
    // Генерация случайного основания хэширования:
    Hash::kBase = gen_base(256, Hash::kMod);
 
    // Создание объектов хэширования:
    Hash hash_a(a), hash_b(b+b);
 
    // Складываем все хэши подстрок исходной длины удвоенной строки b в массиви сортируем:
    std::vector<std::pair<int, ull>> hashes;
    for (int i = 0; i  < (int)b.size(); ++i) {
        hashes.push_back(hash_b(i, b.size(), mxPow));
    }
    std::sort(hashes.begin(), hashes.end());
 
    // Проходим по хэшам строки a и ищем среди хэшей строки b бинарным поиском:
    int answ = 0;
    for (int i = 0; i + (int)b.size() <= (int)a.size(); ++i) {
        answ += std::binary_search(hashes.begin(), hashes.end(), hash_a(i, b.size(), mxPow));
    }
    // Выводим ответ:
    printf("%d", answ);
 
    return 0;
}