#include<bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long ll;
typedef long long int lli;
#define lli 1000010
#define lli2 2000020
 


 // Path and shortest distance
 
 
 
string S[lli];
vector<int> G[lli];
vector<char> value;
vector<char> dir[lli];
vector<int> reachVia,reachDir;
 
int main(){
    int row,col;
    cin>>row>>col;
    for(int i=0;i<row;i++) cin>>S[i];
    int n=row*col+1;
    value.resize(n+1);
    reachVia.resize(n+1);
    reachDir.resize(n+1);
    vector<int> visit(n,0);
    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    char dirs[4]={'U','D','L','R'};
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            char c=S[i][j];
            int node=i*col+j+1;
            value[node]=c;
            if(c=='#'){
                visit[node]=1;
                continue;
            }
            for(int k=0;k<4;k++){
                int x1=i+dx[k];
                int y1=j+dy[k];
                if(x1<0 || y1<0 || x1>=row || y1>=col) continue;
                G[node].push_back(x1*col+y1+1);
                dir[node].push_back(dirs[k]);
            }
        }
    }
    function<void(int,int,int)>bfs=[&](int node,int par,char c){
        queue<int> q;
        q.push(node);
        visit[node]=1;
        reachVia[node]=par;
        reachDir[node]=c;
        while(!q.empty()){
            int newnode=q.front();
            q.pop();
            for(int i=0;i<G[newnode].size();i++){
                int presentnode=G[newnode][i];
                char d=dir[newnode][i];
                if(visit[presentnode]!=1){
                    visit[presentnode]=1;
                    q.push(presentnode);
                    reachVia[presentnode]=newnode;
                    reachDir[presentnode]=d;
                }
            }
        }
    };
    int tar;
    for(int i=0;i<n;i++){
        if(value[i]=='B'){
             tar=i; continue;
        }
        if(value[i]!='A') continue;
        bfs(i,-1,'X');
    }
    if(visit[tar]==0){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    string ans="";
    while(tar!=-1){
        int par=reachVia[tar];
        int c=reachDir[tar];
        if(c!='X') ans+=c;
        tar=par;
    }
    reverse(ans.begin(),ans.end());
    cout<<ans.length()<<endl;
    cout<<ans<<endl;
    return 0;
}