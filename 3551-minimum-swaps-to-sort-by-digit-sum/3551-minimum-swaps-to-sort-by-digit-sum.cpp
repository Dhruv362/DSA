class Solution {
public:
    int getdigsum(int num)
    {
        int sum = 0;
        while(num > 0)
        {
            int d = num%10;
            sum += d;
            num /= 10;
        }
        return sum;
    }
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> aftersorted(nums);
        auto lambda = [this] (int num1, int num2) {
            int num1digsum = getdigsum(num1);
            int num2digsum = getdigsum(num2);

            if(num1digsum != num2digsum)
                return num1digsum < num2digsum;

            return num1 < num2;
        };    

        sort(begin(aftersorted), end(aftersorted), lambda);

        unordered_map<int, int> valtoidx;
        for(int i = 0; i < n; i++)
        {
            valtoidx[nums[i]] = i;
        }

        int swapcount = 0;
        for(int i = 0; i < n; i++)
        {
            int expectedval = aftersorted[i];
            int currval = nums[i];

            if(expectedval == currval) continue;
            int idx = valtoidx[expectedval];
            nums[i] = expectedval;
            nums[idx] = currval;
            valtoidx[expectedval] = i;
            valtoidx[currval] = idx++;
            swapcount++;
        }
        return swapcount;

    }
};