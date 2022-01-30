// Link do código original: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLD-aresta.cpp

// Heavy-Light Decomposition - aresta
//
// SegTree de soma
// query / update de soma das arestas
//
// Complexidades:
// build - O(n)
// query_path - O(log^2 (n))
// update_path - O(log^2 (n))
// query_subtree - O(log(n))
// update_subtree - O(log(n))


#define f first
#define s second
#define MAXN 100010

//Seg [1...n]
namespace seg { 
	int nd[4 * MAXN];
	int v[MAXN], n;
	void build(int i, int l, int r){
		if(l == r) nd[i] = v[l];
		else{
			int m = (l + r)/2;
			build(2 * i, l, m), build(2 * i + 1, m + 1, r);
			nd[i] = max(nd[2 * i], nd[2 * i + 1]);
		}
	}
	int query(int i, int l, int r, int ql, int qr){
		if(l > qr || ql > qr) return MOD;
		else if(ql <= l && r <= qr) return nd[i];
		else{
			int m = (l + r)/2;
			return min(query(2 * i, l, m, ql,q r), query(2 * i + 1, m + 1, r, ql, qr));
		}
	}
	int query(int l, int r){
		return query(1, 1, n, l, r);
	}
	void build(int tam, int aux[]){
		n = tam;
		for(int i = 1; i <= n; i++) v[i] = aux;
		build(1, 1, n);
	}
}

namespace hld {
	vector<pair<int, int> > g[MAXN];
	int pos[MAXN], sz[MAXN];
	int sobe[MAXN], pai[MAXN];
	int h[MAXN], v[MAXN], t;

	void build_hld(int k, int p = -1, int f = 1) {
		v[pos[k] = t++] = sobe[k]; sz[k] = 1;
		for (auto& i : g[k]) if (i.f != p) {
			sobe[i.f] = i.s; pai[i.f] = k;
			h[i.f] = (i == g[k][0] ? h[k] : i.f);
			build_hld(i.f, k, f); sz[k] += sz[i.f];

			if (sz[i.f] > sz[g[k][0].f] or g[k][0].f == p) swap(i, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 1;
		build_hld(root);
		seg::build(t, v);
	}
	ll query_path(int a, int b) {
		if (a == b) return 0;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b]+1, pos[a]);
		return seg::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b, int x) {
		if (a == b) return;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg::update(pos[b]+1, pos[a], x);
		seg::update(pos[h[a]], pos[a], x); update_path(pai[h[a]], b, x);
	}
	ll query_subtree(int a) {
		if (sz[a] == 1) return 0;
		return seg::query(pos[a]+1, pos[a]+sz[a]-1);
	}
	void update_subtree(int a, int x) {
		if (sz[a] == 1) return;
		seg::update(pos[a]+1, pos[a]+sz[a]-1, x);
	}
	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}