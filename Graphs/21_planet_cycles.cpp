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
 
// Understanding the binary lifting 
// Application second about the planet cycle's

int main(){
    int n;
    cin>>n;
    v next(n);
    v2 before(n);
    rep(i,0,n-1){
        int val;
        cin>>val;
        val--;
        next[i]=val;
        before[next[i]].push_back(i);
    }
    vector<map<lld,lld>> cycles;
    v cycle_id(n,-2);
    rep(i,0,n-1){
        if(cycle_id[i]!=-2) continue;
        v path;
        path.emplace_back(i);
        int at=i;
        while(cycle_id[next[at]]==-2){
            at=next[at];
            path.emplace_back(at);
            cycle_id[at]=-3;
        }
        map<lld,lld> cycle;
        bool iscycle=false;
        for(auto node:path){
            iscycle= iscycle || node==next[at];
            if(iscycle){
                cycle[node]=cycle.size();
            }
            cycle_id[node]=iscycle ? cycles.size():-1;
        }
        cycles.push_back(cycle);
    }
    v cycle_dist(n,0);
    rep(i,0,n-1){
        if(cycle_id[next[i]]==-1 || cycle_id[i]!=-1) continue;
        cycle_dist[i]=1;
        v stack(before[i]);
        while(!stack.empty()){
            int back_node=stack.back();
            stack.pop_back();
            cycle_dist[back_node]=cycle_dist[next[back_node]]+1;
            stack.insert(stack.end(),before[back_node].begin(),before[back_node].end());
        }
    }
    int len=ceil(log2(n));
    v2 up(n,v(len+1));
    rep(i,0,n-1) up[i][0]=next[i];
    rep(bit,1,len){
        rep(node,0,n-1){
            up[node][bit]=up[up[node][bit-1]][bit-1];
        }
    }
    auto advance=[&](lld pos,lld dis){
        repD(bit,len,0){
            if(((1<<bit) & dis)!=0) pos=up[pos][bit];
        }
        return pos;
    };
    v ans;
    rep(i,0,n-1){
        if(cycle_dist[i]==0){
            int ids=cycle_id[i];
            int distance=cycles[cycle_id[i]].size();
            ans.push_back(distance);
            continue;
        }
        lld dist1=cycle_dist[i];
        lld nodecycle=advance(i,dist1);
        lld dist2=cycles[cycle_id[nodecycle]].size();
        ans.push_back(dist2+dist1);
    }
    for(auto x:ans) cout<<x<<" ";
    return 0;
}