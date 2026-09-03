class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int,vector<int>> mp;

    for(int i=0;i<reservedSeats.size();i++){
        mp[reservedSeats[i][0]].push_back(reservedSeats[i][1]);
    }

    long long ans=(long long)(n-mp.size())*2;

    for(auto &p:mp){
        vector<int> s(11,0);

        for(int x:p.second) s[x]=1;

        bool l=!s[2]&&!s[3]&&!s[4]&&!s[5];
        bool m=!s[4]&&!s[5]&&!s[6]&&!s[7];
        bool r=!s[6]&&!s[7]&&!s[8]&&!s[9];

        if(l&&r) ans+=2;
        else if(l||m||r) ans+=1;
    }
    return ans;
    }
};