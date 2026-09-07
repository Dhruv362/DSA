class Solution {
public:
    int distinctSubseqII(string s) {
        const int M = 1e9 + 7;

        vector<long long> last(26, 0);
        long long dp = 1;

        for (char c : s) {
            long long ndp = (2 * dp % M - last[c - 'a'] + M) % M;
            last[c - 'a'] = dp;
            dp = ndp;
        }

        return (dp - 1 + M) % M;
    }
};