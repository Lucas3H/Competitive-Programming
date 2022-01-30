// Link do código original: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLD-vertice.cpp

// Heavy-Light Decomposition - vertice
//
// SegTree de soma
// query / update de soma dos vertices
//
// Complexidades:
// build - O(n)
// query_path - O(log^2 (n))
// update_path - O(log^2 (n))
// query_subtree - O(log(n))
// update_subtree - O(log(n))

#define MAXN 100010
//Seg [0...n-1]
// Quando for estudar o código, tentar transformar para [1...n]
int v[MAXN], n;
namespace seg { ... }

namespace hld {
	vector<int> adj[MAXN];
	int pos[MAXN], sz[MAXN];
	int val[MAXN], pai[MAXN];
	int h[MAXN], t;

	void build_hld(int k, int p = -1, int f = 1) {
		pos[k] = t++;
		v[pos[k]] = val[k]; sz[k] = 1;
		for (auto& i : adj[k]) if (i != p) {
			pai[i] = k;
			h[i] = (i == adj[k][0] ? h[k] : i);
			build_hld(i, k, f); sz[k] += sz[i];

			if (sz[i] > sz[adj[k][0]] or adj[k][0] == p) swap(i, adj[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
		build_hld(root);
		seg::build(t, v);
	}
	ll query_path(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b], pos[a]);
		else return seg::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b, int x) {
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) {
			seg::update(pos[b], pos[a], x);
			return;
		}
		seg::update(pos[h[a]], pos[a], x); update_path(pai[h[a]], b, x);		
	}
	
    ll query_subtree(int a) {
		return seg::query(pos[a], pos[a]+sz[a]-1);
	}
	void update_subtree(int a, int x) {
		seg::update(pos[a], pos[a]+sz[a]-1, x);
	}

	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}