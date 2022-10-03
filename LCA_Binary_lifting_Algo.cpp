#include <bits/stdc++.h>
using namespace std;

//Binary Lifting is a dynamic programming approach where we pre-compute an array memo[1, n][1, log(n)]
//where memo[i][j] contains 2^j-th ancestor of node i.
//memo[i][j] = parent[i] if j = 0 and 
//memo[i][j] = memo[memo[i][j – 1]][j – 1] if j > 0 as (2^(j) = 2^(j-1) + 2^(j-1))

// Pre-processing to calculate values of memo[][]
void dfs(int u, int p, vector<vector<int>>& memo, vector<int>& level, int l, vector<vector<int>>& graph){
    memo[u][0] = p;
    for (int i = 1; i <= l; i++) memo[u][i] = memo[memo[u][i - 1]][i - 1];

    for (int v : graph[u])
    {
        if (v != p)
        {
            level[v] = level[u] + 1;
            dfs(v, u, memo, level, l, graph);
        }
    }
}

// Function to return the LCA of nodes u and v
int lca(int u, int v, int l, vector<vector<int>>& memo, vector<int>& level){

    //The node which is present farthest from the root node is taken as u. If v is farther from root
    //node, then swap the two.
    if(level[u]<level[v]) swap(u,v);

    // Finding the ancestor of u which is at same level as v
    for(int i=l; i>=0; i--){
        if((level[u]-pow(2,i)) >= level[v]) u = memo[u][i];
    }

    // If v is the ancestor of u, then v is the LCA of u and v
    if(u==v) return u;

    // Finding the node closest to the root which is not the common ancestor of u and v i.e. a node
    //x such that x is not the common ancestor of u and v but memo[x][0] is.
    for (int i = l; i >= 0; i--){
        if (memo[u][i] != memo[v][i]){
            u = memo[u][i];
            v = memo[v][i];
        }
    }
 
    // Returning the first ancestor of above found node
    return memo[u][0];
}

int main(){
    int n,e;        //n is no of nodes, e is no of edges
    cin>>n>>e;

    vector<vector<int>> graph(n+1);
    for(int i=0; i<e; i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int l = (int) ceil(log2(n));
    vector<vector<int>> memo(n+1, vector<int>(l+1,-1));    //vector to store 2^jth parent of ith node

    vector<int> level(n+1,0); // stores the level of each node

    dfs(1,1,memo,level,l,graph);

    int q;
    cin>>q;
    for(int i=0; i<q; i++){
        int u,v;
        cin>>u>>v;
        cout<<"LCA of "<<u<<" and "<<v<<" is: "<<lca(u,v,l,memo,level)<<endl;
    }
}
