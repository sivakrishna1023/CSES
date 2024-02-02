#include<bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long ll;
typedef long long int lli;
#define test (ll)1e5+7
#define lli2 2000020
 
 
vector<int> G[test];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int node1,node2;
        cin>>node1>>node2;
        G[node1].push_back(node2);
        G[node2].push_back(node1);
    }
    vector<pair<int,int>> ans;
    vector<int> visit(n+1,0);
    function<void(int,vector<int>&)>bfs=[&](int node,vector<int>& vis){
        queue<int> q;
        q.push(node);
        while(!q.empty()){
            int node1=q.front();
            q.pop();
            for(int i=0;i<G[node1].size();i++){
                int presentnode=G[node1][i];
                if(vis[presentnode]==0){
                    vis[presentnode]=1;
                    q.push(presentnode);
                }
            }
        }
    };
    int prev=-1,k=0;
    for(int i=1;i<=n;i++){
          if(visit[i]==0){
            bfs(i,visit);
            if(prev!=-1){
                k++;
                ans.push_back({prev,i});
            }
            prev=i;
          }
    }
    cout<<k<<endl;
    for(auto x:ans){
        cout<<x.first<<" "<<x.second<<endl;
    }
    return 0;
}