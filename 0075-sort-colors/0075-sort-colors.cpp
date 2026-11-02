class Solution {
public:
    void sortColors(vector<int>& nums) {
        unordered_map<int, int> mp;

        for (int i : nums) {
            mp[i]++;
        }

        int noz = mp[0];
        int noo = mp[1];
        int ntw = mp[2];

        int i = 0;

        while (noz--) {
            nums[i++] = 0;
        }

        while (noo--) {
            nums[i++] = 1;
        }

        while (ntw--) {
            nums[i++] = 2;
        }
    }
};