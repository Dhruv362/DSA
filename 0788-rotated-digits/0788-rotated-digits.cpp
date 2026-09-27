class Solution {
public:
    int rotatedDigits(int n) {
        int count = 0;
        for (int num = 1; num <= n; num++) {
            int k = num;
            bool didNumChange = false;
            while (k != 0) {
                int dig = k % 10;
                if (dig == 3 || dig == 4 || dig == 7) {
                    didNumChange = false;
                    break;
                } else if (dig == 2 || dig == 5 || dig == 6 || dig == 9)
                    didNumChange = true;
                k /= 10;
            }
            if (didNumChange)
                count++;
        }
        return count;
    }
};