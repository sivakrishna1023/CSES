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


//Bellman Ford algorithm

// The Bellman-Ford algorithm is used to find the shortest path in a weighted graph, 
// even in the presence of negative edge weights.
vector<lld> G[lli],G2[lli];

struct weights
{
   int a,b;
   ll w;
};
 

vector<bool> bfs(int node,int n,vector<lld> G[]){
    vector<bool> visit(n+1,false);
    queue<lld> q;
    q.push(node);
    while(!q.empty()){
        lld node1=q.front();
        q.pop();
        if(visit[node1]) continue;
        visit[node1]=true;
        for(auto x:G[node1]){
            if(visit[x]) continue;
            q.push(x);
        }
    }
    return visit;
}
int main(){
    ll n,m;
    cin>>n>>m;
    vector<weights> edges(m);
    for(int i=0;i<m;i++){
      int a,b;
      ll w;
      cin>>a>>b>>w;
      w=(-1)*w;
      G[a].push_back(b);
      G2[b].push_back(a);
      edges[i].a=a;
      edges[i].b=b;
      edges[i].w=w;
    }
    vector<bool> isreachable_1=bfs(1,n,G);
    vector<bool> isreachable_n=bfs(n,n,G2);

    vector<ll> shortdis(n+1,1e18);
    shortdis[1]=0;
    bool iscycle=false;
    for(int times=1;times<=n;times++){
        for(auto x:edges){
            if(shortdis[x.a]!=1e18 && shortdis[x.a]+x.w<shortdis[x.b]){
                shortdis[x.b]=shortdis[x.a]+x.w;
                if(times==n){
                    if(isreachable_1[x.b] && isreachable_n[x.b]) iscycle=true;
                }
            }  
        }
    }
    if(iscycle) cout<<-1<<endl;
    else cout<<(-1)*shortdis[n]<<endl;
    return 0;
}