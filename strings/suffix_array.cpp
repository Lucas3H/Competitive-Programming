/* 
	Complexity: O(n log n)
	Memory: O(n)
*/
struct suffixArray{
	int n, len, h/*Coordinate compression and LCP*/;
	vector<int> sa, r/*rank*/, lcp, aux, cnt;

	void countingSort(vector<int> & p, int len){
		fill(cnt.begin(), cnt.end(), 0);
		for(int & x : p) 
			cnt[r[x] + 1]++, x = (x - len + n) % n;
		for(int i = 1; i < n; i++) 
			cnt[i] += cnt[i - 1];
		for(int x : p) 
			aux[cnt[r[x]]++] = x;
		p = aux;
	}

	suffixArray(string s = ""){
		s.push_back('$'), n = s.size(), len = 1, h = 0;
		sa.resize(n), r.resize(n), lcp.resize(n), aux.resize(n), cnt.resize(n + 1);
		
		// Coordinate compression
		map<int, int> m; for(int x : s) m[x] = 1;
		for(auto & x : m) x.second = h++;
		for(int i = 0; i < n; i++) r[i] = m[s[i]], sa[i] = i;
		
		countingSort(sa, 0);
		while(len < n){
			countingSort(sa, len), aux[sa[0]] = 0;
			for(int i = 1; i < n; i++) 
				aux[sa[i]] = aux[sa[i - 1]] + /*Not equal to previous*/\
				(r[sa[i]] != r[sa[i - 1]] || r[(sa[i] + len)%n] != r[(sa[i - 1] + len)%n]); 
			r = aux, len <<= 1;	
		}

		// Build LCP
		h = 0;
		for(int i = 0; i < n; i++){
			if(r[i] > 0){
				int j = sa[r[i] - 1];
				while(s[i + h] == s[j + h]) h++;
				lcp[r[i]] = h;
				if(h > 0) h--;
			}
		}	
	}
};