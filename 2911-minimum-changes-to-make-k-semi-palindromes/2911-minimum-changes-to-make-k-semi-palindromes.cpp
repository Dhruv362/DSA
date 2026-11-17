class Solution {
public:
    int minimumChanges(string s, int k) {
        int n=s.size();
        vector<vector<int>> a(n,vector<int>(n,INT_MAX));
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int len=j-i+1;
                for(int d=1;d<len;d++){
                    if(len%d) continue;
                    int m=len/d,y=0;
                    for(int r=0;r<d;r++){
                        for(int t=0;t<m/2;t++){
                            if(s[i+r+t*d]!=s[i+r+(m-1-t)*d]) y++;
                        }
                    }
                    a[i][j]=min(a[i][j],y);
                }
            }
        }
        vector<vector<int>> dp(n+1,vector<int>(k+1,INT_MAX));
        dp[0][0]=0;
        for(int j=2;j<=n;j++){
            for(int p=1;p<=k;p++){
                for(int i=0;i+2<=j;i++){
                    if(dp[i][p-1]==INT_MAX) continue;
                    dp[j][p]=min(dp[j][p],dp[i][p-1]+a[i][j-1]);
                }
            }
        }
        return dp[n][k];
    }
};