#include <bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long ll;
typedef long long int lli;
#define test 1000010
#define lli2 2000020
 
 
string S[test];
vector<ll> G[test];
vector<char> dir[test];
vector<char> value;
vector<ll> reachedDir,reachedVia;
int main(){
   ll row,col;
   cin>>row>>col;
   for(ll i=0;i<row;i++) cin>>S[i];
   ll n=row*col;
   value.resize(n+1);
   reachedDir.resize(n+1);
   reachedVia.resize(n+1);
   ll dx[4]={-1,1,0,0};
   ll dy[4]={0,0,-1,1};
   char dirs[4]={'U','D','L','R'};
   vector<ll> visited(n+1,0);
   for(int i=0;i<row;i++){
       for(int j=0;j<col;j++){
        ll node=i*col+j+1;
        char c=S[i][j];
        value[node]=c;
          if(c=='#'){
            visited[node]=1;
            continue;
          }
          for(int k=0;k<4;k++){
            ll x=i+dx[k];
            ll y=j+dy[k];
            if(x<0 || y<0 || x>=row || y>=col || S[x][y]=='#') continue;
            G[node].push_back(x*col+y+1);
            dir[node].push_back(dirs[k]);
          }
       }
   }
   function<vector<ll>(ll,ll,char)> bfs=[&](ll node,ll par,char c){
          queue<int> q;
          q.push(node);
          visited[node]=1;
          reachedVia[node]=par;
          reachedDir[node]=c;
          vector<ll> dis(n+1,1e9);
          dis[node]=0;
          while(!q.empty()){
            ll node1=q.front();
            q.pop();
            for(ll i=0;i<(ll)G[node1].size();i++){
                ll newnode=G[node1][i];
                char dir_to=dir[node1][i];
                if(visited[newnode]==0){
                     visited[newnode]=1;
                     q.push(newnode);
                     dis[newnode]=dis[node1]+1;
                     reachedVia[newnode]=node1;
                     reachedDir[newnode]=dir_to;
                }
            }
          }
          return dis;
   };
   ll tar=-1;
   vector<ll> monsterdis(n+1,1e9);
   queue<ll> q;
   for(ll i=1;i<=n;i++){
    if(value[i]=='M') q.push(i), monsterdis[i]=0;
   }
   while(!q.empty()){
      ll node=q.front();q.pop();
      for(ll i=0;i<(ll)G[node].size();i++){
          ll newnode=G[node][i];
          if(monsterdis[newnode]>monsterdis[node]+1){
            monsterdis[newnode]=monsterdis[node]+1;
            q.push(newnode);
          }
      }
   }
   for(ll i=1;i<=n;i++){
     if(value[i]!='A') continue;
     auto me=bfs(i,-1,'X');
     
     for(ll k=1;k<=n;k++){
        if(me[k]<monsterdis[k]){
            ll r=(k-1)/col;
            ll c=(k-1)%col;
            if(r==0 || c==0 || r==row-1 || c==col-1){
                tar=k;
                break;
            }
        }
     }
     break;
   }
   if(tar==-1){
    cout<<"NO"<<endl;
    return 0;
   }
   cout<<"YES"<<endl;
   string ans="";
   while(tar!=-1){
     ll par=reachedVia[tar];
     char c=reachedDir[tar];
     if(c!='X') ans+=c;
     tar=par;
   }
   cout<<ans.length()<<endl;
   reverse(ans.begin(),ans.end());
}