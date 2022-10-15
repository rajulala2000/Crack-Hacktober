int parent[N];
int ran[N];             //define N as per convenience
void make_set(int v) {
    parent[v] = v;
    ran[v]=0;
}
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v]=find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b){
      if(ran[a]<ran[b])swap(a,b);
      parent[b] = a;
      if(ran[a]==ran[b])ran[a]++;
      //ran[a]+=ran[b];
    }
}
