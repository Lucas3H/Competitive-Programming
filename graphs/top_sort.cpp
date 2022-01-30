// 
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
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 987654321

struct graph{
	int v, e;
	set<int> adj[MAXN]; // Evitar arestas múltiplas
	int tin[MAXN], pr[MAXN], comp[MAXN], low_link[MAXN];
};

int ord[MAXN];
int clock = 1;

void top_sort(){
	graph go = g;

	for(int i = 1; i <= go.v; i++) ord[i] = 0;		
	
	set<int> in_edges[MAXN];

	for(int i = 1; i <= go.v; i++){
		for(auto x: go.adj[i]) in_edges[x].pb(i);
	}

	queue<int> fila;

	for(int i = 1; i <= go.v; i++){
		if(in_edges[i].size() == 0){
			fila.push(i);
		}
	}

	while(!fila.empty()){
		int davez = fila.front();
		fila.pop();

		ord[davez] = clock++;

		for(auto x: go.adj[davez]){
			in_edges[x].erase(davez);

			if(in_edges[x].size() == 0) fila.push(x);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
}
