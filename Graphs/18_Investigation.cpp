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
#define mod static_cast<int>(1e9 + 7)
#define MINUS_INF INT_MIN/2 


vector<ll> G[lli],W[lli];
struct weights
{
   int a,b;
   ll w;
};
int main(){
    int n,m;
    cin>>n>>m;
    while(m--){
        ll node1,node2,w;
        cin>>node1>>node2>>w;
        G[node1].push_back(node2);
        W[node1].push_back(w);
    }
    priority_queue<pa,vector<pa>,greater<pa>> q;
    vector<int> dp(n+1,MINUS_INF);
    vector<ll> dis(n+1,1e18);
    vector<ll> number(n+1,-n-100);
    vector<ll> mini_flights(n+1,1e9);
    vector<ll> max_flights(n+1,MINUS_INF);
    number[1]=1;
    mini_flights[1]=1;
    max_flights[1]=1;
    q.push({0,1});
    while(!q.empty()){
         auto top=q.top(); q.pop();
         ll node1=top.second;
         ll dis1=top.first;
         if(dis1>dis[node1]) continue;
         for(int i=0;i<G[node1].size();i++){
            ll node2=G[node1][i];
            ll wt=W[node1][i];
            if(dis[node2]>dis1+wt){
                dis[node2]=dis1+wt;
                number[node2]=number[node1];
                mini_flights[node2]=mini_flights[node1]+1;
                max_flights[node2]=max_flights[node1]+1;
                q.push({dis[node2],node2});
            }else if(dis[node2]==dis1+wt){
                number[node2]=(number[node1]+number[node2])%mod;
                mini_flights[node2]=min(mini_flights[node2],mini_flights[node1]+1);
                max_flights[node2]=max(max_flights[node2],max_flights[node1]+1);
            }
            
         }
    }
    cout<<dis[n]<<" "<<number[n]<<" "<<mini_flights[n]-1<<" "<<max_flights[n]-1<<endl;
    return 0;
}