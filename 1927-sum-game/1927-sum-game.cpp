class Solution {
public:
    bool sumGame(string num) {
        int n=num.size();
        int l=0,r=0,a=0,b=0;

        for(int i=0;i<n/2;i++){
            if(num[i]=='?') a++;
            else l+=num[i]-'0';
        }

        for(int i=n/2;i<n;i++){
            if(num[i]=='?') b++;
            else r+=num[i]-'0';
        }

        if((a+b)%2) return true;

        return 2*(l-r)!=9*(b-a);
    }
};