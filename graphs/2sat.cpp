/*
    Algorythm to solve 2-SAT problems in O(n)
	Clousures goes from [1...n]
	
*/

#define MAXN 200010

vector <int> g[MAXN], gr[MAXN];
int n;

struct SAT{
    vector<bool> used, ans;
    vector<int> order, comp;
    int tot = 0;

    void dfs1 (int v) {
        used[v] = true;
        for (size_t i=0; i<g[v].size(); ++i)
            if (!used[ g[v][i] ])
                dfs1 (g[v][i]);
        order.push_back (v);
    }

    void dfs2 (int v, int c) {
        used[v] = true;
        comp[v] = c;
        for (size_t i=0; i<gr[v].size(); ++i)
            if (!used[ gr[v][i] ])
               dfs2 (gr[v][i], c);
    }

    /*
		{A, B} means A -> B, {-A, B} means !A -> B, ans so on
    */
    bool solve(vector<pii> & v){
        comp.assign(2*n, -1), order.clear(), used.assign (2*n, false);
        	
        fr(i, 2*n){
        	g[i].clear();
        	gr[i].clear();
        }

        for(auto p : v){
        	if(p.f < 0) p.f = -2*p.f - 1;
        	else p.f = 2*p.f - 2;

        	if(p.s < 0) p.s = -2*p.s - 1;
        	else p.s = 2*p.s - 2;

        	g[p.f].push_back(p.s);
        	gr[p.s].push_back(p.f);
        }

        for (int i=0; i < 2*n; ++i)
            if (!used[i])
                dfs1 (i);

        used.assign (2*n, false);
        tot = 0;

        for (int i=0; i<2*n; ++i) {
            int v = order[2*n-1-i];
            if (!used[v]) {
                dfs2 (v, tot++);
            }
        }

        ans.assign(n, false);
	    for (int i = 0; i < 2*n; i += 2) {
	        if (comp[i] == comp[i + 1])
	            return false;
	        ans[i / 2] = comp[i] > comp[i + 1];
	    }
	    return true;
    }
};

int main() {
    SAT s;
    s.build();
}