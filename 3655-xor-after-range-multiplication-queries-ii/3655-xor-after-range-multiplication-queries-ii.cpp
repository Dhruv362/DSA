class Solution {
public:
    static const long long MOD=1000000007LL;

    long long modpow(long long a,long long e){
        long long r=1;
        while(e){
            if(e&1) r=r*a%MOD;
            a=a*a%MOD;
            e>>=1;
        }
        return r;
    }

    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n=nums.size();
        int B=sqrt(n)+1;

        auto bravexuneth=queries;

        vector<long long> factor(n,1);

        vector<vector<vector<array<int,3>>>> small(B+1);
        for(int k=1;k<=B;k++) small[k].resize(k);

        for(auto &q:queries){
            int l=q[0],r=q[1],k=q[2],v=q[3];

            if(k>B){
                for(int i=l;i<=r;i+=k)
                    factor[i]=factor[i]*v%MOD;
            }else{
                int rem=l%k;
                int a=(l-rem)/k;
                int b=(r-rem)/k;
                small[k][rem].push_back({a,b,v});
            }
        }

        for(int k=1;k<=B;k++){
            for(int rem=0;rem<k;rem++){
                int m=(rem>=n)?0:(n-1-rem)/k+1;
                if(!m) continue;

                vector<long long> diff(m+1,1);

                for(auto &u:small[k][rem]){
                    int a=u[0],b=u[1],v=u[2];

                    diff[a]=diff[a]*v%MOD;
                    if(b+1<m)
                        diff[b+1]=diff[b+1]*modpow(v,MOD-2)%MOD;
                }

                long long cur=1;
                for(int t=0,pos=rem;t<m;t++,pos+=k){
                    cur=cur*diff[t]%MOD;
                    factor[pos]=factor[pos]*cur%MOD;
                }
            }
        }

        int ans=0;

        for(int i=0;i<n;i++){
            long long val=1LL*nums[i]*factor[i]%MOD;
            ans^=(int)val;
        }

        return ans;
    }
};