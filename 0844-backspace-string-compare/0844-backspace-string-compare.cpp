class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char>sts;
        stack<char>stt;
        int i = 0;
        while(i < s.size()){
            if(s[i] != '#')
                sts.push(s[i]);
            else
                if(!sts.empty())
                    sts.pop();
            i++;
        }
        i = 0;
        while(i < t.size()){
            if(t[i] != '#')
                stt.push(t[i]);
            else
                if(!stt.empty())
                    stt.pop();
            i++;
        }
        if(stt.empty() && sts.empty())
            return true;
        if(sts.size() != stt.size())
            return false;
        
        while(!sts.empty()){
            if(sts.top() != stt.top())
                return false;
            stt.pop();
            sts.pop();
        }
        return true;

    }
};