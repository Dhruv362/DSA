class Solution {
public:
    string removeDuplicates(string s) {
        string st = "";
        for(char ch:s){
            if(!st.empty()){
                if(st.back() == ch){
                    st.pop_back();
                }else{
                    
                st.push_back(ch);
                }
            }else{
                st.push_back(ch);
            }
        }
        return st;
    }
};