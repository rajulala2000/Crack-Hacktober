#include <bits/stdc++.h>
using namespace std;

int inf = 1e9;

int main(){
    int v,e;
    cin>>v>>e;
    vector<vector<int>> edges;
    for(int i=0; i<e; i++){
        int a,b,w;        //directed edge from a to b
        cin>>a>>b>>w;
        edges.push_back({a,b,w});
    }
    int src;
    cin>>src;
    int dist[v];
    memset(dist,inf,sizeof(dist));

    dist[src] = 0;
    for(int i=0; i<v-1; i++){
        for(auto x: edges){
            int a = x[0], b = x[1], w = x[2];
            if(dist[a]!=inf && dist[a]+w<dist[b]){
                dist[b] = dist[a]+w;
            }
        }
    }

    int negcycle = 0;
    for(auto x: edges){
        int a = x[0], b = x[1], w = x[2];
        if(dist[a]!=inf && dist[a]+w<dist[b]){
            negcycle = 1;
            break;
        }
    }
    if(negcycle) cout<<"Negative cycle exist"<<endl;
    else{
        cout<<"vertex dist_from_src"<<endl;
        for(int i=0; i<v; i++) cout<<i<<" "<<dist[i]<<endl;
        cout<<endl;
    }
}
