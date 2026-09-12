class Solution {
public:
    int divide(int a, int b) {
        if (a == INT_MIN && b == -1) return INT_MAX;
        long long x = llabs((long long)a);
        long long y = llabs((long long)b);
        long long q = 0;
        while (x >= y) {
            long long t = y, c = 1;
            while ((t << 1) <= x) {
                t <<= 1;
                c <<= 1;
            }
            x -= t;
            q += c;
        }
      if ((a < 0) ^ (b < 1)) q = -q;
             return (int)q;
    }
};