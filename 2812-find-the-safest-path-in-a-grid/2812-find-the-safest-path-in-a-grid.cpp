class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        vector<vector<int>>vis(grid.size(),vector<int>(grid[0].size(),0));
        int total=grid.size()*grid[0].size();
        priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>>pq;
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid[i].size();j++)
            {
                if(grid[i][j]==1)
                {
                    pq.push({0,i,j});
                    grid[i][j]=0;
                    total--;
                    vis[i][j]=1;
                }
            }
        }
        vector<int>dx={0,1,0,-1};
        vector<int>dy={1,0,-1,0};
        while(!pq.empty())
        {
            auto [a,b,c]=pq.top();
            pq.pop();
            for(int i=0;i<4;i++)
            {
                int nx=b+dx[i];
                int ny=c+dy[i];
                if(nx>=0 && ny>=0 && nx<grid.size() && ny<grid[0].size() && !vis[nx][ny])
                {
                     vis[nx][ny] = 1;
                    grid[nx][ny]=a+1;
                    pq.push({a+1,nx,ny});
                }
            }
        }
         vector<int>dx1={0,1,0,-1};
        vector<int>dy1={1,0,-1,0};
        priority_queue<tuple<int,int,int>>pq1;
        pq1.push({grid[0][0],0,0});
        int ans=0;
        vector<vector<int>> vis2(grid.size(), vector<int>(grid[0].size(),0));
        while(!pq1.empty())
        {
            auto [a,b,c]=pq1.top();
            if(b==grid.size()-1 && c==grid[0].size()-1)return a;
            pq1.pop();
            for(int i=0;i<4;i++)
            {
            int nx=b+dx1[i];
                int ny=c+dy1[i];
                if(nx>=0 && ny>=0 && nx<grid.size() && ny<grid[0].size()&&
           !vis2[nx][ny] )
                {
                   vis2[nx][ny]=1;
                   int s=min(grid[nx][ny],a);
                    pq1.push({s,nx,ny});
                }
            }
            
        }
        return ans;
    }
};