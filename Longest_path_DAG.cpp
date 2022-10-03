#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

void toposort(int u, vi& vis, stack<int>& s, vector<vpii>& adj){
    vis[u] = true;
    for(auto v: adj[u]){
        int x = v.first;
        if(!vis[x]){
            toposort(x,vis,s,adj);
        }
    }
    s.push(u);
}

int main(){
    int v,e;
    cin>>v>>e;
    vector<vpii> adj(v);
    vi indegree(v,0);
    for(int i=0; i<e; i++){
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back({b,w});
        indegree[b]++;
    }

    int src;
    cin>>src;

    vi dist(v,-inf);
    vi vis(v,0);

    stack<int> topoorder;
    toposort(src,vis,topoorder,adj);

    dist[src] = 0;
    //Using Topological sorting

    while(!topoorder.empty()){
        int i = topoorder.top();
        topoorder.pop();
        for(auto x: adj[i]){
            int w = x.second, u = x.first;
            if(dist[u]<dist[i]+w) dist[u] = dist[i]+w;
        }
    }
    

    for(int i=0; i<v; i++){
        if(dist[i]==-inf) cout<<"INF ";
        else cout<<dist[i]<<" ";
    }
    
}
