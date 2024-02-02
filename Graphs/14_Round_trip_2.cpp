#include <bits/stdc++.h>
#include <iostream>
#include <climits>
#include <string>
using namespace std;
 
typedef long long int lld;
typedef long long ll;
typedef pair<lld,lld> PA;
typedef float f;
typedef double d;
typedef vector<lld> v;
typedef vector<d> vd;
typedef vector<v> v2;
typedef vector<PA> vp;
 
#define lim 1000010
#define test 1000010 
#define lli (lld)1e5+7
#define lli2 2000020
#define extreme ((1<<30)-1)
#define INF INT_MAX/2;
#define PI acos(-1)
#define allones 1099511627775
 
#define rep(i,a,n) for(lld i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(lld i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
#define debugv(v) for(auto x:v) cout<<x<<" ";
#define endline cout<<endl;
#define find_s1_in_s(s,s1) cout<<std::search(s.begin(), s.end(), s1.begin(), s1.end())<<endl;
 
static const auto speedup = []() {
std::ios::sync_with_stdio(false); std::cin.tie(nullptr); return 0;}();
 
class Solution {
public:
   void solve(){  
   }
};
 
 
// cycle finding in the directed graph
// We are using the 2 array's they are visited array and pathvisited array 
// we user curr array instand of parent array here
// For clear view refer striver  cycle detection in directed cycle

vector<lld> G[lli];
int main(){
    lld n,m;
    cin>>n>>m;
    rep(i,0,m-1){
        lld a,b;
        cin>>a>>b;
        G[a].push_back(b);
    }
    vector<int> ans, curr;
    vector<bool> visit(n+1,false),pathvisit(n+1,false);
    bool cycle=false;
    function<void(int,int)> dfs=[&](int x,int par){
        if(visit[x]){
            if(cycle || !pathvisit[x]) return;
            cycle=true;
            int path=false;
            for(auto node:curr){
                if(node==x) path=true;
                if(path) ans.push_back(node);
            }
            ans.push_back(x);
            return;
        }
        curr.push_back(x);
        visit[x]=true;
        pathvisit[x]=true;
        for(auto nodes:G[x]){
            dfs(nodes,x);
        }
        curr.pop_back();
        pathvisit[x]=false;
    };
    rep(i,1,n){
        if(visit[i]) continue;
        dfs(i,-1);
    }
    if(!cycle){
        cout<<"IMPOSSIBLE\n";
    }else{
        cout<<ans.size()<<endl;
        for(auto x:ans) cout<<x<<" ";
    }
    return 0;
}