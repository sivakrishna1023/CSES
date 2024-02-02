#include<bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
typedef long long ll;
typedef long long int lli;
 

// Basic BFS



class Solution{
    public:
    bool isvalid(int x,int y,int n,int m){
        return (x>=0 && y>=0 && x<n && y<m);
    }
    void dfs(int x,int y,int n,int m,vector<vector<char>>& grid){
          grid[x][y]='#';
          int dx[]={-1,1,0,0};
          int dy[]={0,0,-1,1};
          for(int i=0;i<4;i++){
            int newx=x+dx[i];
            int newy=y+dy[i];
            if(isvalid(newx,newy,n,m) && grid[newx][newy]=='.'){
                dfs(newx,newy,n,m,grid);
            }
          }
    }
    int countrooms(int n,int m,vector<vector<char>>& grid){
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                  if(grid[i][j]=='.'){
                    ans++;
                    dfs(i,j,n,m,grid);
                  }
            }
        }
        return ans;
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>> grid(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>grid[i][j];
        }
    }
    Solution s1;
    int ans=s1.countrooms(n,m,grid);
    cout<<ans<<endl;
    return 0;
}