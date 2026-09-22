class Solution {
public:
    vector<int> searchRange(vector<int>& arr, int target) {
        if(arr.size() == 0) return {-1,-1};
        int i = 0; int j = arr.size() - 1;
        int lowerbound = -1;
        while(i <= j){
            int mid = i + ((j-i) >> 1);
            if(arr[mid] == target) lowerbound = mid;
            if(arr[mid] >= target){
                j = mid - 1;
            }
            else i = mid + 1;
        }
        int upperbound = -1;
        i = 0 ; j = arr.size() - 1;
        while(i <= j){
            int mid = i + ((j - i) >> 1);
            if(arr[mid] == target) upperbound = mid;
            if(arr[mid] > target) j = mid - 1;
            else i = mid + 1;
        }
        return {lowerbound , upperbound};
    }
};