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
#define MOD (int)(1e9+7)
const lld inf = LLONG_MAX/10;


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

struct edge{
    int x,y;
    lld cap,flow;
};

struct Graph_flow{
    vector<edge> e;
    vector<int> curr,d;
    vector<vector<int>> adj;
    int n,source,sink;
    Graph_flow(){}
    Graph_flow(int v){
        n=v;
        curr=vector<int>(n+1);
        d=vector<int>(n+1);
        adj=vector<vector<int>>(n+1);
    }
    void add_edge(int from, int to, lld cap){
        edge e1={from,to,cap,0};
        edge e2={to,from,0,0};
        adj[from].push_back(e.size());e.push_back(e1);
        adj[to].push_back(e.size());e.push_back(e2);
    }
    void add_bi_edge(int from,int to,lld cap){
        edge e1={from,to,cap,0};
        edge e2={to,from,cap,0};
        adj[from].push_back(e.size());e.push_back(e1);
        adj[to].push_back(e.size());e.push_back(e2);
    }
    int bfs(){
        queue<int> q;
        for(int i=0;i<=n;i++) d[i]=-1;
        q.push(source);
        d[source]=0;
        while(!q.empty() && d[sink]<0){
            int x=q.front();q.pop();
            for(int i=0;i<(int)adj[x].size();i++){
                int id=adj[x][i],y=e[id].y;
                if(d[y]<0 && e[id].flow<e[id].cap){
                    q.push(y);
                    d[y]=d[x]+1;
                }
            }
        }
        return d[sink]>=0;
    }
    lld dfs(int x,lld flow){
        if(!flow) return 0;
        if(x==sink) return flow;
        for(;curr[x]<(int)adj[x].size();++curr[x]){
            int id=adj[x][curr[x]],y=e[id].y;
            if(d[y]!=d[x]+1) continue;
            int pushed=dfs(y,min(flow,e[id].cap-e[id].flow));
            if(pushed){
                e[id].flow+=pushed;
                e[id^1].flow-=pushed;
                return pushed;
            }
        }
        return 0;
    }
    lld maxflow(int src,int snk){
        this->source=src,this->sink=snk;
        lld flow=0;
        while(bfs()){
            for(int i=0;i<=n;i++) curr[i]=0;
            while(int pushed=dfs(source,inf)){
                flow+=pushed;
            }
        }
        return flow;
    }
};

struct MiddleElement{
      MiddleElement(int k){
           sizeleft=k;
      }
      void balance(){
          while(sz(left)<sizeleft){
              sum+=*right.begin();
              left.insert(*right.begin());
              right.erase(right.begin());
          }
          while(sz(left)>sizeleft){
              sum-=*left.rbegin();
              right.insert(*left.rbegin());
              left.erase(left.find(*left.rbegin()));
          }
      }
      void insert(int x){
            if(x<*left.rbegin()) left.insert(x),sum+=x;
            else right.insert(x);
            balance();
      }
      void erase(int x){
          auto it=right.find(x);
          if(it!=right.end()) right.erase(it);
          else sum-=x, left.erase(left.find(x));
          balance();
      }
      multiset<int> left,right;
      long long sum=0;
      int sizeleft;
};

int main(){
   int t;
   cin>>t;
   vector<int> a(t);
   rep(i,0,t-1) cin>>a[i];
   vector<vector<long long>> dp(1e6+10,vector<long long>(2,0));
   dp[1][0]=1;
   dp[1][1]=1;
   for(int i=2;i<=1e6+5;i++){
      dp[i][0]=static_cast<long long>(2)*dp[i-1][0]+dp[i-1][1];
      dp[i][1]=static_cast<long long>(4)*dp[i-1][1]+dp[i-1][0];
       dp[i][0]%=MOD;
       dp[i][1]%=MOD;
   }
   rep(i,0,t-1){
       cout<<(dp[a[i]][0]+dp[a[i]][1])%MOD<<"\n";
   }
   return 0;
}