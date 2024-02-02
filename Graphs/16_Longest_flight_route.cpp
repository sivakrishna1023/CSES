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


vector<ll> G[lli];
vector<int> reached;
struct weights
{
   int a,b;
   ll w;
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> indeg(n+1,0);
    while(m--){
        int node1,node2;
        cin>>node1>>node2;
        G[node1].push_back(node2);
        indeg[node2]++;
    }
    vector<int> par(n+1,-1);
    vector<int> dp(n+1,-n-1);
    dp[1]=1;
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(indeg[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int top=q.front();
        q.pop();
        for(auto x:G[top]){
            if(dp[top]+1>dp[x]){
                dp[x]=dp[top]+1;
                par[x]=top;
            }
            indeg[x]--;
            if(indeg[x]==0) q.push(x);
        }
    }
    int val=n;
    vector<int> ans;
    if(dp[n]<0){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    while(val!=-1){
        ans.push_back(val);
        val=par[val];
    }
    int size=ans.size();
    cout<<size<<endl;
    for(int i=size-1;i>=0;i--){
        cout<<ans[i]<<" ";
    }
    return 0;
}