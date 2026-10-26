class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        long long massL = mass;
        sort(asteroids.begin(), asteroids.end());
        for (int i = 0; i < asteroids.size(); i++)
            if (asteroids[i] > massL)
                return false;
            else
                massL += asteroids[i];
        return true;
    }
};