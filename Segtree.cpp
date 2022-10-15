//SIMPLE
int n,st[4*N],a[N];
void build(int node,int tl,int tr,int a[]){
if(tl==tr)st[node]=a[tl];

else{
int tm=(tl+tr)/2;
build(2*node,tl,tm,a);
build(2*node+1,tm+1,tr,a);
st[node]=st[2*node]+st[2*node+1];
}
return ;
}

int sum(int node,int tl,int tr,int l,int r){
if(l>r)return 0;
else if(l==tl&&r==tr)return st[node];
int tm=(tl+tr)/2;
return sum(node*2,tl,tm,l,min(r,tm))+sum(2*node+1,tm+1,tr,max(l,tm+1),r);
}

void update(int node,int tl,int tr,int pos,int val){
if(tl==tr)st[node]=val;
else{
 int tm=(tl+tr)/2;
 if(pos<=tm)update(2*node,tl,tm,pos,val);
 else update(2*node+1,tm+1,tr,pos,val);
 st[node]=st[2*node]+st[2*node+1];
}
}

// LAZY
struct LazySeg {
    int l, r;
    int val = 0, tag = 0;
    bool is_lazy = false;
    LazySeg * l_child = NULL, * r_child = NULL;

    LazySeg(int _l, int _r) {
        l = _l;
        r = _r;
        if (r - l > 1) {
            int m = (l + r) / 2;
            l_child = new LazySeg(l, m);
            r_child = new LazySeg(m, r);
        }
    }~LazySeg() {
        delete l_child;
        delete r_child;
    }
    void unlazy() {
        if (!is_lazy) return;
        val = (r - l) * tag;
        if (r - l <= 1) return;
        l_child -> tag = tag;
        l_child -> is_lazy = true;
        r_child -> tag = tag;
        r_child -> is_lazy = true;
        tag = 0;
        is_lazy = false;
    }
    void update(int from, int to, int x) {
        unlazy();
        if (from >= r || l >= to) return;
        if (from <= l && to >= r) {
            tag = x;
            is_lazy = true;
            unlazy();
        } else {
            l_child -> update(from, to, x);
            r_child -> update(from, to, x);
            val = l_child -> val + r_child -> val;
        }
    }
    int query(int from, int to) {
        if (from >= r || l >= to) return 0;
        unlazy();
        if (from <= l && to >= r) return val;
        else {
            if (l_child == NULL) return 0;
            return l_child -> query(from, to) + r_child -> query(from, to);
        }
    }
    //pre = prefix in [l,k)
    int max_right(int k, int pre, int v) {
        unlazy();
        if (r - l == 1) {
            if (val == v) return l;
            else return l - 1;
        }
        l_child -> unlazy();
        int mid = (l + r) / 2;
        if (mid <= k) {
            return r_child -> max_right(k, pre - l_child -> val, v);
        } else if (l_child -> val - pre == v * (mid - k)) {
            //left to mid-1 has all 1's => answer must be >= mid-1
            return r_child -> max_right(mid, 0, v);
        } else {
            return l_child -> max_right(k, pre, v);
        }
    }
    //suff = suffix
    int get_answer() {
        unlazy();
        if (r - l == 1) {
            if (val == 1) return l;
            else return l - 1;
        }
        r_child -> unlazy();
        if (r_child -> val == 0) {
            //[mid to end] are all 0
            return l_child -> get_answer();
        } else {
            return r_child -> get_answer();
        }
    }
};

