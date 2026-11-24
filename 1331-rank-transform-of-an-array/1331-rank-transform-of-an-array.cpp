class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        vector <pair<int,int>> temp(n);
        for (int i=0;i<n;i++){
            temp[i]={arr[i],i};
        }
        int pos=0;
        int  l =-997890;
        sort(temp.begin(),temp.end());
        for (int i=0;i<n;i++){
            if (temp[i].first!=l){
                pos++;
                l=temp[i].first;
            }
            arr[temp[i].second]=pos;
        }
        return arr;
        
    }
};