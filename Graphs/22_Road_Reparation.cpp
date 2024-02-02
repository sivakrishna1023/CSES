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
#define lim1 300010
#define mod static_cast<int>(1e9 + 7)
#define MINUS_INF INT_MIN/2 


vector<ll> G[lli],W[lli];
ll mat[lim1][30];
struct weights
{
   int a,b;
   ll w;
};




// Minimumm spanning Tree (Prim's Algorithm)

int main(){
      ll n,m;
      cin>>n>>m;
      while(m--){
        ll a,b,w;
        cin>>a>>b>>w;
        G[a].push_back(b);
        W[a].push_back(w);
        G[b].push_back(a);
        W[b].push_back(w);
      }
      priority_queue<pa,vector<pa>,greater<pa>> pq;
      pq.push({0,1});
      vector<int> visit(n+1,0);
      visit[0]=1;
      ll ans=0;
      while(!pq.empty()){
            ll node=pq.top().second;
            ll dis1=pq.top().first;
            pq.pop();
            if(visit[node]==1) continue;
            ans+=dis1;
            visit[node]=1;
            for(int i=0;i<G[node].size();i++){
                ll node2=G[node][i];
                ll dis2=W[node][i];
                if(!visit[node2]){
                    pq.push({dis2,node2});
                }
            }
      }
      for(int i=0;i<n+1;i++){
        if(!visit[i]){
          cout<<"IMPOSSIBLE"<<endl;
          return 0;
        }
      }
      cout<<ans<<endl;
      return 0;
}