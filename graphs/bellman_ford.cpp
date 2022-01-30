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
typedef pair<int, int> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define INF 1000000007

/*
	COMPLEXIDADE: O(V*E)

	O algoritmo serve para calcularmos a menor distância de todos os vértices, a um vértice inicial V.
	É como um Dijkstra, mas ele aceita arestas negativas, mas não aceita ciclos de soma total negativa.
	Prova-se que até a i-ésima iteração, todos os menores caminhos que contém i arestas foram vistos e
	portanto, serão necessárias (n-1) iterações. Em particular, se na n-ésima iteração houver alguma 
	atualização, então o grafo com certeza tem um ciclo de soma total negativa.
*/

/*
	Para achar explicitamente o caminho mínimo, basta criar um vetor pai[MAXN], no qual p[i] é o último
	vértice que atualizou i, i.e., dist[i] = dist[p[i]] + w.
*/
struct edge{
	int weight, v1, v2;
};

int n;
int dist[MAXN];
vector<edge> edges;

int bellman_ford(int v){
	for(int i = 1; i <= n; i++) dist[i] = INF;
	dist[v] = 0;

	int atualizou = 0;
	for(int i = 0; i < n; i++){
		atualizou = 0;

		for(auto x: edges){
			if(dist[x.v1] == INF) continue;

			if(dist[x.v2] > dist[x.v1] + x.weight){
				dist[x.v2] = dist[x.v1] + x.weight;
				atualizou = 1;
			}
		}
	}

	if(atualizou) return 1; // contém um ciclo negativo
	else return 0;
}

int main(){
	ios::sync_with_stdio(false);
}
