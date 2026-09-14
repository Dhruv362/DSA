
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int bp = -1;
        for(int i = 0; i + 1 < n; i++) {
            if(nums[i] < nums[i + 1]) {
                bp = i;
            }
        }
        if(bp == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        int justLargestIdx = -1;
        for(int i = bp + 1; i < n; i++) {
            if(nums[bp] < nums[i]) {
                justLargestIdx = i;
            }
        }
        swap(nums[bp], nums[justLargestIdx]);
        reverse(nums.begin() + bp + 1, nums.end());
    }
};
