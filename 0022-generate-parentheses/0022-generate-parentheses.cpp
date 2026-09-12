class Solution {
public:
    vector<string> v;

    void f(int o,int c,int n,string s){
        if(s.size()==2*n){
            v.push_back(s);
            return;
        }

        if(o<n) f(o+1,c,n,s+'(');
        if(c<o) f(o,c+1,n,s+')');
    }

    vector<string> generateParenthesis(int n) {
        f(0,0,n,"");
        return v;
    }
};