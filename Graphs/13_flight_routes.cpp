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
#define lli2 2000020



vector<ll> G[lli],W[lli];

struct weights
{
   int a,b;
   ll w;
};
int main(){
    ll n,m,k;
    cin>>n>>m>>k;
    for(int i=0;i<m;i++){
      int a,b;
      ll w;
      cin>>a>>b>>w;
      G[a].push_back(b);
      W[a].push_back(w);
    }
    priority_queue<pa,vector<pa>,greater<pa>> pq;
    vector<multiset<ll>> dist(n+1);
    vector<int> visit(n+1,k);
    pq.push({0,1});
    vector<ll> ans;
    while(!pq.empty()){
         ll dis1=pq.top().first;
         ll node1=pq.top().second;
         pq.pop();
         if(visit[node1]==0) continue;
         visit[node1]--;
         for(int i=0;i<G[node1].size();i++){
            ll node2=G[node1][i];
            ll dis2=W[node1][i];
            if(dist[node2].size()<k){
                dist[node2].insert(dis1+dis2);
                pq.push({dis1+dis2,node2});
            }else if(*dist[node2].rbegin()>dis1+dis2){
                dist[node2].erase(std::prev(dist[node2].end()));
                dist[node2].insert(dis1+dis2);
                pq.push({dis1+dis2,node2});
            }
         }
    }
    for(auto x:dist[n]) cout<<x<<" ";
    cout<<endl;
    return 0;
}