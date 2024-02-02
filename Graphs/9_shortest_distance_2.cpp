#include <bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n)<<(shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long int lld;
typedef pair<lld,lld> PA;
typedef long long ll;
#define test 1000010 
#define lli (lld)1e5+7
#define lli2 2000020
#define num 510
 
 
// Floyd Warshall Algorithm



vector<PA> q(lli);
vector<vector<ll>> dis(num, vector<ll>(num, 1e18));
int main(){
    ll n,m,q1;
    cin>>n>>m>>q1;
    for(int i=0;i<m;i++){
        ll a,b,w;
        cin>>a>>b>>w;
        dis[a][b]=min(dis[a][b],w);
        dis[b][a]=min(dis[a][b],w);
    }
     vector<PA> q(q1);
    for(int i=0;i<q1;i++){
        lld a,b;
        cin>>a>>b;
        q[i]={a,b};
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
           for(int k=1;k<=n;k++){
               if(j==k){
                dis[j][k]=0; 
                continue;
               }
               if(dis[j][k]>dis[j][i]+dis[i][k]){
                dis[j][k]=dis[j][i]+dis[i][k];
              }
           }
        }
    }
    for(int i=0;i<q1;i++){
        auto nodes=q[i];
        int firstnode=nodes.first;
        int secondnode=nodes.second;
        if(dis[firstnode][secondnode]!=1e18){
            cout<<dis[firstnode][secondnode]<<endl;
        }else{
            cout<<-1<<endl;
        }
    }
    return 0;
}