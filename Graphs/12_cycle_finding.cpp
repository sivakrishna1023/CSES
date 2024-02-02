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
 
 
// General ditection of cycle in directed Graphs we use the two vector visit and pathvisit
// But here we have to find the path too and the constant's also less in size so we can go with Bellman Ford algo
// which give's solution for detection of negative edge's
 
struct edges
{
   int a,b;
   lld w;
};
int main(){
    lld n,m;
    cin>>n>>m;
    edges vals[m];
    rep(i,0,m-1){
        int a,b;
        lld c;
        cin>>a>>b>>c;
        vals[i].a=a;
        vals[i].b=b;
        vals[i].w=c;
    }
    vector<lld> dis(n+1,0),par(n+1,-1);
    bool negcycle=false;
    int cyclepoint=-1;
    rep(times,1,n){
        rep(node,0,m-1){
        //   auto [a,b,w]=vals[node];
        int a=vals[node].a;
        int b=vals[node].b;
        int w=vals[node].w;
          if(dis[a]+w<dis[b]){
             if(times==n){
                negcycle=true;
                cyclepoint=b;
             }
              dis[b]=dis[a]+w;
              par[b]=a;
          }
        }
    }
    if(!negcycle){
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
    rep(i,1,n) cyclepoint=par[cyclepoint];
    lld start=cyclepoint;
    vector<lld> ans;
    while(true){
        ans.push_back(start);
        start=par[start];
        if(start==cyclepoint) break;
    }
    ans.push_back(start);
    reverse(ans.begin(),ans.end());
    for(auto x:ans) cout<<x<<" ";
    return 0;
}