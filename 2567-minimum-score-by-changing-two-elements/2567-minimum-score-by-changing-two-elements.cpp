class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        if (n < 3) return 0;

        int a = abs(nums[2] - nums[n-1]);
        int b = abs(nums[n-3] - nums[0]);
        int c = abs(nums[1] - nums[n-2]);

        return min({a, b, c});
    }
};