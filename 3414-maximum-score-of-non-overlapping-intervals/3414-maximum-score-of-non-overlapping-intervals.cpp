class Solution {
public:
    struct Node{
        long long s;
        vector<int> v;
    };

    static bool lexsm(const vector<int>& a, const vector<int>& b) {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    static Node best(const Node& a, const Node& b) {
        if (a.s != b.s) return a.s > b.s ? a : b;
        return lexsm(a.v, b.v) ? a : b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(a.begin(), a.end());

        vector<long long> st(n);
        for (int i = 0; i < n; i++) st[i] = a[i][0];

        vector<int> nxt(n);
        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(st.begin(), st.end(), a[i][1]) - st.begin();
        }

        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        for (int i = n - 1; i >= 0; i--) {
            dp[i][0] = {0, {}};

            for (int k = 1; k <= 4; k++) {
                Node skip = dp[i + 1][k];

                Node take;
                take.s = a[i][2] + dp[nxt[i]][k - 1].s;
                take.v = dp[nxt[i]][k - 1].v;
                take.v.push_back((int)a[i][3]);
                sort(take.v.begin(), take.v.end());

                dp[i][k] = best(skip, take);
            }
        }

        return dp[0][4].v;
    }
};