#include <bits/stdc++.h>
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
    ll n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        ll node1,node2;
        cin>>node1>>node2;
        G[node1].push_back(node2);
        G[node2].push_back(node1);
    }
    vector<int> visit(n+1,0);
    vector<int> curr,ans;
    bool cycle=false;
    function<void(ll,ll)> dfs=[&](ll node,ll par){
         if(visit[node]!=0){
            if(cycle) return;
            cycle=true;
            int start=false;
            for(auto x:curr){
                if(x==node) start=true;
                if(start)ans.push_back(x);
            }
            ans.push_back(node);
            return;
         }
         visit[node]=1;
         curr.push_back(node);
         for(auto x:G[node]){
            if(x!=par) dfs(x,node);
         }
         curr.pop_back();
    };
    for(int i=1;i<=n;i++){
        if(visit[i]!=0) continue;
        dfs(i,0);
    }
    if(!cycle){
        cout<<"IMPOSSIBLE"<<endl;
    }else{
        cout<<ans.size()<<endl;
        for(auto x:ans) cout<<x<<" ";
    }
    return 0;
}