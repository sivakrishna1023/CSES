#include <bits/stdc++.h>
#include <iostream>
#include <climits>
using namespace std;
#define LSOP(n, shift) ((n) << (shift))
#define RSOP(n,shift)  ((n)>>(shift))
#define lim 1000010
typedef long long ll;
typedef long long int lli;
#define test (ll)1e5+7
#define lli2 2000020
 
vector<ll> G[test];
 
int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        ll node1, node2;
        cin >> node1 >> node2;
        G[node1].push_back(node2);
        G[node2].push_back(node1);
    }
    vector<ll> visit(n + 1, 0);
    vector<ll> group(n + 1);
    std::function<bool(ll, vector<ll>&, vector<ll>&)> bfs = [&](ll node, vector<ll>& visit, vector<ll>& group) {
        visit[node] = 1;
        group[node] = 1;
        queue<pair<int, int>> q;
        q.push({node, group[node]});
        while(!q.empty()){
            auto top = q.front();
            q.pop();
            int node1 = top.first;
            int group1 = top.second;
            for(int i = 0; i < G[node1].size(); i++){
                int newnode = G[node1][i];
                if(visit[newnode] == 1){
                    if(group[newnode] == group1) return false;
                } else if(visit[newnode] == 0){
                    visit[newnode] = 1;
                    group[newnode] = (group1 == 1) ? 2 : 1;
                    q.push({newnode, group[newnode]});
                }
            }
        }
        return true;
    };
    bool ispossible = true;
    for(int i = 1; i <= n; i++){
        if(visit[i] == 0){
           bool val=bfs(i,visit,group);
           ispossible= ispossible && val;
        }
    }
    if(!ispossible){
        cout << "IMPOSSIBLE" << endl;
    } else {
        for(int i = 1; i <= n; i++){
            cout << group[i] << " ";
        }
    }
    return 0;
}