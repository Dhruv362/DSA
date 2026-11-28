class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size(), cheapestItem = INT_MAX;

        vector<int> frq(n + 1, 0);
        for(auto& item : items){
            frq[item[0]]++;
            cheapestItem = min(cheapestItem, item[1]);
        }

        vector<int> fSum(n + 1, 0);
        for(int i = 1; i <= n; i++){
            for(int j = i; j <= n; j += i){
                fSum[i] += frq[j];
            }
        } 

        vector<pair<int, int>> units;
        for(auto& item : items){
            int count = fSum[item[0]] - 1;
            if(count > 0 && item[1] < 2 * cheapestItem) units.push_back({item[1], count});
        }

        sort(units.begin(), units.end());

        int res = 0;
        for(auto& [price, fCount] : units){
            int k = min(fCount, budget / price);
            budget -= k * price;
            res += 2 * k;
        }

        res += budget / cheapestItem;
        return res;
    }
};