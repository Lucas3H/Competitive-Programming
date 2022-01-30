/*
	Floyd-Warshall algorithm
	Goal: find minimal distance between any two vertices. Graph may have 
	negative weight, but no negative cycle
	Complexity: O(n^3)
*/

#define MAXN 1000

int d[MAXN][MAXN];
int n;

void floyd(){
	for (int k = 0; k < n; ++k) {
	    for (int i = 0; i < n; ++i) {
	        for (int j = 0; j < n; ++j) {
	            d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
	        }
	    }
	}
}

void build(){
	int e;
	cin >> n >> e;
	for(int i = 0; i < e; i++){
		int u, v, w;
		cin >> u >> v >> w;
		d[u][v] = w;
		d[v][u] = w;
	}

	for(int i = 0; i < n; i++){
		d[i][i] = 0;
	}
}