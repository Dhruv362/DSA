class Solution {
public:
    vector<string> ans;
    vector<string> mp={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

    void dfs(string& d,int i,string s){
        if(i==d.size()){
            ans.push_back(s);
            return;
        }

        for(char c:mp[d[i]-'0'])
            dfs(d,i+1,s+c);
    }

    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};

        dfs(digits,0,"");
        return ans;
    }
};