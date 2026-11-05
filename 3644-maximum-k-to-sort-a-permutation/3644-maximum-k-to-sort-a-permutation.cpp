class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int output = -1;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i) {
                if (output == -1) output = nums[i];
                else output &= nums[i];
            }
        }
        return (output >= 0 ? output : 0);
    }
};