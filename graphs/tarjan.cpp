// Find Strongly Connected Components in O(n + e)
#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int, int> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define INF 1000000000
#define MAXL 30
#define ROOT 1

struct graph{
	int v, e;
	set<int> adj[MAXN]; // Evitar arestas múltiplas
	int tin[MAXN], pr[MAXN], comp[MAXN], low_link[MAXN];
};

int t = 0;

graph g, meta;
stack<int> s;
int n_scc = 1;

void makeComp(int id){
	while(true){
		int st = s.top();

		g.low_link[st] = INF; // Evitar cross-edges
		g.tin[st] = INF; // Evitar cros-edges
		g.comp[st] = n_scc;
		s.pop();
		
		if(st == id) break;
	}

	n_scc++;
}

void dfs(int v){
	g.pr[v] = 1;
	g.tin[v] = t++;
	g.low_link[v] = g.tin[v];
	s.push(v);

	for(auto x: g.adj[v]){
		if(!g.pr[x]){
			dfs(x);
		}

		g.low_link[v] = min(g.low_link[v], g.low_link[x]);
	}

	if(g.low_link[v] == g.tin[v]){
		makeComp(v);
	}
}

void read(){
	cin >> g.v >> g.e;

	t = 0;
	n_scc = 1;

	frr(i, g.v + g.v){
		g.adj[i].clear();

		meta.adj[i].clear();
		g.tin[i] = 0;
		g.pr[i] = 0;
		g.comp[i] = 0;
		g.low_link[i] = 0;

		meta.tin[i] = 0;
		meta.pr[i] = 0;
		meta.comp[i] = 0;
		meta.low_link[i] = 0;
	}


	fr(i, g.e){
		int v1, v2;
		cin >> v1 >> v2;

		g.adj[v1].insert(v2);
	}

	g.v += g.v;

	return 1;
}

void tarjan(){
	frr(i, g.v){
		if(!g.pr[i]){
			t = 0;
			dfs(i);
		}
	}

	/*------------Build metagraph------------*/

	meta.v = n_scc-1;

	frr(i, g.v){
		int v1 = g.comp[i], v2;
		for(auto x: g.adj[i]){
			v2 = g.comp[x];
			if(v1 == v2) continue; // Evitar v -> v

			meta.adj[v1].insert(v2);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);

	read();
	tarjan();

}
