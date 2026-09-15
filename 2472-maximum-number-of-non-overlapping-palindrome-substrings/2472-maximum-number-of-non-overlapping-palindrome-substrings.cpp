class Solution {
public:
    static bool isPalindrome(const char* s, size_t n) {
        return std::equal(s, s + n / 2, std::make_reverse_iterator(s + n));
    }

    size_t maxPalindromes(string_view s, size_t k) {
        auto x = s.data(), e = x + s.size();
        size_t r = 0;
        while (x + k <= e) {
            bool a = isPalindrome(x, k);
            bool b = a || isPalindrome(x, k + 1);
            r += b;
            x += !a + (k & -size_t{a || b});
        }
        return r;
    }
};