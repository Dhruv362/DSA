class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<char, int> mp;
        string ans;
        for (char c : s) {
            mp[c]++;
        }
        priority_queue<pair<int, char>>pq;
        for (auto it : mp) {
            int first = it.second;
            char second = it.first;
            pq.push({first, second});
        }

        while (!pq.empty()) {
            auto node = pq.top();
            pq.pop();
            int count = node.first;
            char str = node.second;
            for(int i = 0; i < count; i++){
                ans += str;
            }
        }
        // sort(s.begin(),s.end(),[&](b > a));
        return ans;
    }
};