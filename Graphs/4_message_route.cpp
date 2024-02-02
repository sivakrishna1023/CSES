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
 
 
// Path


vector<ll> G[test];
int main(){
    ll n,m;
    cin>>n>>m;
    for(ll i=0;i<m;i++){
        ll node1,node2;
        cin>>node1>>node2;
        G[node1].push_back(node2);
        G[node2].push_back(node1);
    }
    vector<pair<ll,ll>> ans;
    vector<ll> dis(n+1,1e18);
    vector<ll> path(n+1,n);
    path[1]=1;
    dis[1]=0;
    function<void(ll,vector<ll>&,vector<ll>&)>bfs=[&](ll node,vector<ll>& dis,vector<ll>& path){
         queue<pair<ll,ll>> pq;
         pq.push({dis[node],node});
         while(!pq.empty()){
            ll dis1=pq.front().first;
            ll node1=pq.front().second;
            pq.pop();
            for(ll i=0;i<G[node1].size();i++){
                ll currentnode=G[node1][i];
                ll currecntdis=dis[currentnode];
                if(currecntdis>1+dis1){
                    pq.push({1+dis1,currentnode});
                    dis[currentnode]=1+dis1;
                    path[currentnode]=node1;
                }
            }
         }
    };
    bfs(1,dis,path);
    if(dis[n]==1e18){
        cout<<"IMPOSSIBLE"<<endl;
    }
    else{
        cout<<++dis[n]<<endl;
        vector<ll> ans;
        ll par=n;
        while(par!=1){
            ans.push_back(par);
            par=path[par];
        }
        cout<<1<<" ";
        for(int i=ans.size()-1;i>=0;i--){
            cout<<ans[i]<<" ";
        }
    }
return 0;
}