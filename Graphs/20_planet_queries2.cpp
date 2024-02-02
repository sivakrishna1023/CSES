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
 
// just an application of binary lifting 
// Another intution is that we made it as union find problem as there is only one outgoing edge (An observation on cycle_id's)

int main(){
    int n,q;
    cin>>n>>q;
    v next(n);
    v2 before(n);
    rep(i,0,n-1){
        cin>>next[i];
        next[i]--;
        before[next[i]].push_back(i);
    }
    v cycle_id(n,-2);
    vector<map<int,int>> cycles;
    rep(i,0,n-1){
        if(cycle_id[i]!=-2) continue;
        vector<int> path;
        path.emplace_back(i);
        int at=i;
        while(cycle_id[next[at]]==-2){
            at=next[at];
            cycle_id[at]=-3;
            path.push_back(at);
        }
        map<int,int> cycle;
        bool iscycle=false;
        for(int node:path){
            iscycle= iscycle || node==next[at];
            if(iscycle) {cycle[node]=cycle.size();}
            cycle_id[node]= iscycle ? cycles.size() : -1; 
        }
        cycles.push_back(cycle);
    }
    v cycle_dist(n);
    rep(i,0,n-1){
        if(cycle_id[next[i]]==-1 || cycle_id[i]!=-1) continue;
        cycle_dist[i]=1;
        vector<lld> stack(before[i]);
        while(!stack.empty()){
            int node=stack.back();
            stack.pop_back();
            cycle_dist[node]=cycle_dist[next[node]]+1;
            stack.insert(stack.end(),before[node].begin(),before[node].end());
        }
    }
    int len=ceil(log2(n));
    vector<vector<lld>> up(n, vector<lld>(len + 1));
    rep(i,0,n-1) up[i][0]=next[i];
    rep(bit,1,len){
        rep(node,0,n-1){
            up[node][bit]=up[up[node][bit-1]][bit-1];
        }
    }
    auto advance=[&](lld pos,lld dist){
        repD(bit,len,0){
            if((dist & (1<<bit))!=0) pos=up[pos][bit];
        }
        return pos;
    };
    while(q--){
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        if(cycle_id[up[u][len]]!=cycle_id[up[v][len]]){
            cout<<-1<<"\n";  
            continue;
        }
        if(cycle_id[u]!=-1 || cycle_id[v]!=-1){
                if(cycle_id[v]==-1 && cycle_id[u]!=-1){
                    cout<<-1<<"\n"; 
                    continue;
                }
                lld dist1=cycle_dist[u];
                lld ucycle=advance(u,dist1);
                map<int,int> &reqcycle=cycles[cycle_id[ucycle]];
                lld u_ind=reqcycle[ucycle];
                lld v_ind=reqcycle[v];
                lld diff= u_ind<=v_ind ? v_ind - u_ind :reqcycle.size()-(u_ind-v_ind);
                cout<<dist1+diff<<"\n";
        }else{
            if(cycle_dist[v]>cycle_dist[u]){
                cout<<-1<<"\n";
                continue;
            }
            lld dist=cycle_dist[u] - cycle_dist[v];
            cout<< ( advance(u,dist)==v ? dist : -1 ) << "\n";
        }
        
    }
    return 0;
}