#include <bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long int lld;
typedef pair<lld,lld> PA;
typedef long long ll;
typedef long long int lli;
#define test 1000010
#define lli (ll)1e5+7
#define lli2 2000020
 
 
// Dijkstra’s Algorithm



vector<ll> G[lli],W[lli];
int main(){
    ll n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        G[a].push_back(b);
        W[a].push_back(w);
    }
    vector<lld> dis(n+1,LLONG_MAX),visit(n+1,0);
    priority_queue<PA,vector<PA>,greater<PA>> q;
    q.push({0,1});
    dis[1]=0;
    while(!q.empty()){
        auto top=q.top();q.pop();
        lld node=top.second;
        lld dis1=top.first; 
        if(visit[node]==1) continue;
        visit[node]=1;
        for(int i=0;i<G[node].size();i++){
            lld node1=G[node][i];
            lld dis2=W[node][i];
            if(dis[node1]>dis1+dis2){
                dis[node1]=dis1+dis2;
                q.push({dis[node1],node1});
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dis[i]<<" ";
    }
    return 0;
}