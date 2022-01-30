#define MAXN 100010

class Vertex {
public: 
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

class PersistentSeg{
public:
    Vertex * version[MAXN];
    int n, v;    

    Vertex* build(int tl, int tr) {
        if (tl == tr)
            return new Vertex(0);
        int tm = (tl + tr) / 2;
        return new Vertex(build(tl, tm), build(tm+1, tr));
    }

    int get_sum(Vertex* v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && tr == r)
            return v->sum;
        int tm = (tl + tr) / 2;
        return get_sum(v->l, tl, tm, l, min(r, tm))
             + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
    }

    Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
        if (tl == tr)
            return new Vertex(new_val);
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
        else
            return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
    }

    
    PersistentSeg() : n(0) {};
    PersistentSeg(int x){
        n = x, v = 1;
        version[0] = build(1, n);
    }

    int query(int l, int r, int time){
        return get_sum(version[time], 1, n, l, r);
    }

    void add(int pos, int new_val){
        version[v++] = update(version[v-1], 1, n, pos, new_val);
    }
};