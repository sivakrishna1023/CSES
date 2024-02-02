#include <bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long int lld;
typedef long long ll;
typedef pair<lld,lld> PA;
typedef pair<lld,PA> PA2;
typedef pair<ll,ll> pa;
typedef pair<ll,pa> pa2;

#define lli (lld)1e5+7
#define lli1 (lld)1e6+7
#define lli2 2000020

// There are Two way's to solve this problem
// 1. Layers 
//2. instand of two layers consider two graphs for first graph find shortest distance
//from 1st node, and another form last node now remove each edge and consider as its weight as w/2.



vector<ll> G[lli1],W[lli1];

int main(){
    ll n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        ll a,b,w;
        cin>>a>>b>>w;
        G[a].push_back(b);
        W[a].push_back(w);
        
        G[a+n].push_back(b+n);
        W[a+n].push_back(w);
        ll l=w/2;
        G[a].push_back(b+n);
        W[a].push_back(l);
    }
    G[0].push_back(1);
    W[0].push_back(0);
    G[0].push_back(1+n);
    W[0].push_back(0);
    G[n].push_back(2*n+3);
    W[n].push_back(0);
    G[2*n].push_back(2*n+3);
    W[2*n].push_back(0);
    vector<ll> dist(2*n+4,1e18);
    dist[0]=0;
    priority_queue<pa,vector<pa>,greater<pa>> pq;
    pq.push({0,0});
    vector<bool> visit(2*n+4,false);
    while(!pq.empty()){
      ll dis1=pq.top().first;
      ll node1=pq.top().second;
      pq.pop();
       if(visit[node1]) continue;
      visit[node1]=true;
      for(int i=0;i<G[node1].size();i++){
           ll node2=G[node1][i];
           ll dis2=W[node1][i];
           if(dist[node2]>dis1+dis2){
            dist[node2]=dis1+dis2;
            pq.push({dist[node2],node2});
           }
      }
    }
    cout<<dist[2*n+3]<<endl;
    return 0;
}