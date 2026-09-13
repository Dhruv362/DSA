class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& w) {
        vector<int> a;
        int n = s.size(), m = w.size(), k = w[0].size();

        unordered_map<string, int> mp;
        for (auto &x : w) mp[x]++;

        for (int i = 0; i < k; i++) {
            unordered_map<string, int> cur;
            int l = i, c = 0;

            for (int r = i; r + k <= n; r += k) {
                string t = s.substr(r, k);

                if (mp.count(t)) {
                    cur[t]++;
                    c++;

                    while (cur[t] > mp[t]) {
                        string u = s.substr(l, k);
                        cur[u]--;
                        l += k;
                        c--;
                    }

                    if (c == m) {
                        a.push_back(l);

                        string u = s.substr(l, k);
                        cur[u]--;
                        l += k;
                        c--;
                    }
                } else {
                    cur.clear();
                    c = 0;
                    l = r + k;
                }
            }
        }

        return a;
    }
};