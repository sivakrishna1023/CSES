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


// Basic Topological sort

vector<ll> G[lli];
struct weights
{
   int a,b;
   ll w;
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> indeg(n+1);
    while(m--){
        int node1,node2;
        cin>>node1>>node2;
        G[node1].push_back(node2);
        indeg[node2]++;
    }
    vector<int> ans;
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(indeg[i]==0) q.push(i);
    }
    while(!q.empty()){
        int top=q.front();
        q.pop();
        ans.push_back(top);
        for(auto x:G[top]){
            indeg[x]--;
            if(indeg[x]==0) q.push(x);
        }
    }
    if(ans.size()!=n){
        cout<<"IMPOSSIBLE"<<endl;
    }else{
        for(auto x:ans) cout<<x<<" ";
    }
    return 0;
}