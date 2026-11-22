class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        
        vector<int>pref(n);
        pref[0] = 0;
        for(int i = 1; i < n; i++) pref[i] = pref[i-1] + (nums[i] - nums[i-1] <= maxDiff);

        vector<bool> ans;
        for(auto& q : queries){
            int u = q[0];
            int v = q[1];
            if(u==v){ ans.push_back(true);continue;}
            ans.push_back(v-u == pref[v] - pref[u]);

        }
        return ans;
    }
};