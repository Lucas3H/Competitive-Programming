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

/*
	Algoritmo de Dijkstra: calcular a distância entre vértices em um grafo cujas
	arestas tem pesos.

	Complexidade: O(E + V log V)
*/

class Graph{
	public:
		int n, m;
		int dist[MAXN];
		vector<pii> adj[MAXN];

		void dijkstra(int v){
			frr(i, n) dist[i] = MOD;

			pq<pii, vector<pii>, greater<pii>> fila;
			fila.push(mp(0, v));

			while(true){
				int davez = -1;

				while(!fila.empty()){
					pii p = fila.top();
					fila.pop();

					if(dist[p.s] > p.f){
						dist[p.s] = p.f;
						davez = p.s;

						break;
					}
				}

				if(davez == -1) break;

				for(pii e: adj[davez]){
					if(dist[e.f] > dist[davez] + e.s){
						fila.push(mp(dist[davez] + e.s, e.f));
					}
				}
			}
		}

		void read(){
			cin >> n >> m;

			frr(i, m){
				int v1, v2, w;
				cin >> v1 >> v2 >> w;

				adj[v1].pb(mp(v2, w));
				adj[v2].pb(mp(v1, w));
			}
		}
};

int main(){
	ios::sync_with_stdio(false);
	read();
	dijkstra(1);
	frr(i, n) cout << dist[i] << endl;
}
