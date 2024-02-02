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
#define repDI(i,a,n) for(int i = (a); i >= (n); --i);
#define debugv(v) for(auto x:v) cout<<x<<" ";
#define debugvp(v) for(auto&[a,b]:v) cout<<"{"<<a<<" "<<b<<"}"<<" "; cout<<"\n";
#define find_s1_in_s(s,s1) cout<<std::search(s.begin(), s.end(), s1.begin(), s1.end())<<endl;
#define convet_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower); 
#define sz(a) ((int)a.size())

static const auto speedup = []() {
std::ios::sync_with_stdio(false); std::cin.tie(nullptr); return 0;}();

class DSU{
    vector<int> par,size;
    public:
    DSU(int n){
        par.resize(n+1);
        size.resize(n+1);
        for(int i=0;i<=n;i++){
            par[i]=i;
            size[i]=1;
        }
    }
    int find_par(int node){
        if(node==par[node]) return node;
        return par[node]=find_par(par[node]);
    }
    int join_and_size(int u,int v){
        int par_u=find_par(u);
        int par_v=find_par(v);
        if(par_v==par_u) return max(size[par_u],size[par_v]);
        if(size[par_u]<size[par_v]){
            par[par_u]=par_v;
            size[par_v]+=size[par_u];
            return size[par_v];
        }else{
            par[par_v]=par[par_u];
            size[par_u]+=size[par_v];
            return size[par_u];
        }
    }
};

struct StrongDAG{
    public:
    StrongDAG(int n):n(n){
        G.resize(n+1);
        revG.resize(n+1);
        dagG.resize(n+1);
    }
    void add_weight(int u,int v){
        G[u].push_back(v);
        revG[v].push_back(u);
    }
    void process(){
       vector<int> visit(n+1,0);
       vector<int> order;
       function<void(int)> dfs=[&](int node){
           if(visit[node]!=0) return;
           visit[node]=1;
           for(auto x:G[node]){
               dfs(x);
           }
           order.push_back(node);
       };
       for(int i=1;i<=n;i++){
           if(visit[i]==0) dfs(i);
       }
       reverse(order.begin(),order.end());
       visit.assign(n+1,0);
       dag_n=0;
       function<void(int,int)> revdfs=[&](int node,int par){
           if(visit[node]!=0) return;
           visit[node]=par;
           for(auto x:revG[node]){
               revdfs(x,par);
           }
       };
       for(auto x:order){
           if(visit[x]==0){
               revdfs(x,x);
               ++dag_n;
               rootNodes.push_back(x);
           }
       }
       root=visit;
       for(int u=1;u<=n;u++){
           for(auto v:G[u]){
               if(root[u]!=root[v]) dagG[root[u]].push_back(root[v]);
           }
       }
    }
    int n,dag_n;
    vector<int> root,rootNodes;
    vector<vector<int>> G,revG,dagG;
};

// Find Eulerian Path in an directed graph

vector<lld> G[lli2];
lld x[lli2],y[lli2];
lld used[lli2];
int main(){
   lld n,m;
   cin>>n>>m;
   vector<lld> degrees(n+1,0);
   rep(i,1,m){
       cin>>x[i]>>y[i];
       G[x[i]].push_back(i);
       degrees[x[i]]++;
       degrees[y[i]]--;
   }
   rep(i,1,n){
       if(degrees[i]!=0 && i!=1 && i!=n){
           cout<<"IMPOSSIBLE\n";
           return 0;
       }
   }
   if(degrees[1]!=1 || degrees[n]!=-1){
       cout<<"IMPOSSIBLE\n";
       return 0;
   }
   x[m+1]=1;
   y[m+1]=n;
   G[n].push_back(m+1);
   degrees[1]--;
   degrees[n]++;
   // Edges case's
   vector<lld> stack,ans;
   stack.push_back(1);
   while(!stack.empty()){
       lld top=stack.back();
       if(sz(G[top])==0){
           stack.pop_back();
           ans.push_back(top);
           continue;
       }
       int back=G[top].back();
       int v=x[back]+y[back]-top;
       G[top].pop_back();
       stack.push_back(v);
   }
   if(sz(ans)!=m+2){
       cout<<"IMPOSSIBLE\n";
       return 0;
   }
   reverse(ans.begin(),ans.end());
   int ind=-1,lastone=-1;
   for(int i=0;i<sz(ans)-1;i++){
       if(ans[i]==n && ans[i+1]==1){
           ind=i;
           break;
       }
       if(ans[i]==1) lastone=i;
   }
   vector<lld> ans2;
   rep(i,lastone,ind){
       ans2.push_back(ans[i]);
   }
   ans.erase(ans.begin()+lastone,ans.begin()+ind+1);
   rep(i,1,sz(ans2)-1){
       ans.push_back(ans2[i]);
   }
   for(auto x:ans){
       cout<<x<<" ";
   }
   return 0;
}