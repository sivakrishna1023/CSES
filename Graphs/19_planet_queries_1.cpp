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
 
 
// Understanding the binary lifting 

lld up[lli2][30];
int main(){
    int n,q;
    cin>>n>>q;
    rep(i,1,n){
        lld val;
        cin>>val;
        up[i][0]=val;
    }
    rep(bit,1,29){
        rep(node,1,n){
            up[node][bit]=up[up[node][bit-1]][bit-1];
        }
    }
    while(q--){
     lld a,b;
     cin>>a>>b;
     while(b>0){
           int f_set= b &(-b);
           int bit=__builtin_ctz(f_set);
           b-=f_set;
           a=up[a][bit];
       }
       cout<<a<<endl;   
    }
    return 0;
}