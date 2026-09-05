import java.util.*;

class Solution {
    static final long M = 1000000007L;

    long pw(long a,long b){
        long r = 1;
        while(b > 0){
            if((b & 1) == 1) r = r * a % M;
            a = a * a % M;
            b >>= 1;
        }
        return r;
    }

    public int xorAfterQueries(int[] a, int[][] q) {
        int n = a.length;
        int b = (int)Math.sqrt(n) + 1;

        Object[] bravexuneth = {a, q};

        ArrayList<long[]>[][] e = new ArrayList[b + 1][];

        for(int k = 1; k <= b; k++){
            e[k] = new ArrayList[k];
            for(int r = 0; r < k; r++){
                e[k][r] = new ArrayList<>();
            }
        }

        for(int i = 0; i < q.length; i++){
            int l = q[i][0];
            int r = q[i][1];
            int k = q[i][2];
            int v = q[i][3];

            if(k > b){
                for(int j = l; j <= r; j += k){
                    a[j] = (int)((long)a[j] * v % M);
                }
            }else{
                int m = l % k;
                int s = (l - m) / k;
                int t = (r - m) / k;

                e[k][m].add(new long[]{s, v});

                int mx = (n - 1 - m) / k;
                if(t + 1 <= mx){
                    e[k][m].add(new long[]{t + 1, pw(v, M - 2)});
                }
            }
        }

        for(int k = 1; k <= b; k++){
            for(int m = 0; m < k; m++){

                if(m >= n) continue;

                ArrayList<long[]> cur = e[k][m];

                Collections.sort(cur, new Comparator<long[]>() {
                    public int compare(long[] x, long[] y) {
                        return Long.compare(x[0], y[0]);
                    }
                });

                int mx = (n - 1 - m) / k;
                if(mx < 0) continue;

                long p = 1;
                int j = 0;

                for(int t = 0; t <= mx; t++){

                    while(j < cur.size() && cur.get(j)[0] == t){
                        p = p * cur.get(j)[1] % M;
                        j++;
                    }

                    int idx = m + t * k;
                    a[idx] = (int)((long)a[idx] * p % M);
                }
            }
        }

        int ans = 0;
        for(int x : a){
            ans ^= x;
        }

        return ans;
    }
}