#ifndef SUFFIX_ARRAY_HPP
#define SUFFIX_ARRAY_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#define dbg(x)  cout << #x << " = " << x << endl
#define dbgv(x)  cout << #x << " = ";for(auto y : x) cout << y << " "; cout << endl;


using namespace std;



struct suffixArray{
	vector<int> s;
	vector<int> sa, lcp, rank;

	int get_max(const vector<int> & v){
		int maximo = 0;
		for(auto x : v) maximo = max(x, maximo);
		return maximo;
	}

	// Normaliza o alfabeto para que seja no máximo o tamanho de v
	void normalize(vector<int> & v){
		int maximo = get_max(v);
		vector<vector<int>> aux(maximo + 1);
		for(size_t i = 0; i < v.size(); i++)
			aux[v[i]].push_back((int)i);

		int tot = 0;
		for(size_t i = 0; i < aux.size(); i++){
			if(aux[i].size() > 0){
				tot++;
				for(int x : aux[i]) v[x] = tot;
			}
		}
	}

	void countingSort(vector<int> & v, const vector<int> & t, int nxt){
		vector<vector<int>> bucket(get_max(t) + 1);
		for(size_t i = 0; i < v.size(); i++)
			bucket[t[v[i] + nxt]].push_back(v[i]);
		
		v.clear();
		for(size_t i = 0; i < bucket.size(); i++)
			for(size_t j = 0; j < bucket[i].size(); j++)
				v.push_back(bucket[i][j]);
	}

	vector<int> buildT0T1(vector<int> t){
		vector<int> aux, t01(t.size()), vals(t.size());
		for(size_t i = 0; i < t.size(); i++) 
			aux.push_back((int)i);
		t.push_back(0), t.push_back(0);
		for(int i = 2; i >= 0; i--) 
			countingSort(aux, t, i);

		for(size_t i = 1; i < vals.size(); i++){
			vals[i] = vals[i - 1];
			for(size_t j = 0; j < 3; j++){
				if(t[aux[i] + j] != t[aux[i - 1] + j]){
					vals[i]++;
					break;
				}
			}
		}

		int tot = 0;
		for(size_t i = 0; i < aux.size(); i++) {
			if(aux[i]%3 == 0){
				t01[aux[i] / 3] = vals[i];
				tot++;
			}
		} 
		for(size_t i = 0; i < aux.size(); i++) 
			if(aux[i]%3 == 1)
				t01[aux[i] / 3 + tot] = vals[i];

		t01.resize(2 * tot - (aux.size()%3 == 1));
		return t01;
	}

	// Retorna true se sufixo[a] < sufixo[b]
	// a%3 == 2 sempre e b%3 == 0 ou 1
	bool comp(int a, int b, const vector<int> & t, const vector<int> & rank){
		if(t[a] != t[b]) return t[a] < t[b];

		if(b%3 == 0){
			if(t[a + 1] != t[b + 1]) return t[a + 1] < t[b + 1];
			else return rank[a + 1] < rank[b + 1];
		}
		else{
			if(t[a + 1] != t[b + 1]) return t[a + 1] < t[b + 1];
			else if(t[a + 2] != t[b + 2]) return t[a + 2] < t[b + 2];
			else return rank[a + 2] < rank[b + 2];
		}
	}

	vector<int> merge(vector<int> t, vector<int> sa01, vector<int> sa2){
		t.push_back(-1), t.push_back(-1);
		vector<int> rank(t.size());

		int tot = 0;
		for(int & x : sa01) rank[x] = tot++;

		vector<int> sa;
		size_t i = 0, j = 0;
		while(i < sa01.size() || j < sa2.size()){
			if(i == sa01.size()) sa.push_back(sa2[j++]);
			else if(j == sa2.size()) sa.push_back(sa01[i++]);
			else{
				if(comp(sa2[j], sa01[i], t, rank)) sa.push_back(sa2[j++]);
				else sa.push_back(sa01[i++]);
			}
		}

		return sa;
	}

	vector<int> buildSA(vector<int> t){
		normalize(t);
		if(t.size() <= 3){
			vector<pair<int, int>> ret;
			vector<int> sa;
			for(size_t i = 0; i < t.size(); i++){
				int sum = 0, p = 25;
				for(size_t j = i; j < t.size(); j++){
					sum += p * (t[j] + 1);
					p /= 5;
				}
				ret.push_back({sum, i});
			}
			sort(ret.begin(), ret.end());
			
			for(size_t i = 0; i < ret.size(); i++){
				sa.push_back(ret[i].second);
			}
			return sa;
		}


		vector<int> t01 = buildT0T1(t);
		vector<int> sa01 = buildSA(t01), sa2;

		for(size_t i = 0; i < t01.size(); i++)
			if(0 < sa01[i] && 3 * sa01[i] - 1 < (int)t.size())
				sa2.push_back(3 * sa01[i] - 1);
		countingSort(sa2, t, 0);

		for(int & x : sa01){
			if(x < ((int)sa01.size() + 1) / 2) x = 3 * x;
			else x = (x - ((int)sa01.size() + 1) / 2) * 3 + 1;
		}

		return merge(t, sa01, sa2);
	}

	suffixArray(string S){
		for(auto x : S) s.push_back(x - 'a' + 1);
		s.push_back(0);

		lcp.resize(s.size()), rank.resize(s.size());
		sa = buildSA(s);

		for(int i = 0; i < (int)sa.size(); i++)
			rank[sa[i]] = i;
		int h = 0;
		for(size_t i = 0; i < s.size(); i++){
			if(rank[i] > 0){
				int j = sa[rank[i] - 1];
				while(s[i + h] == s[j + h]) h++;
				lcp[rank[i]] = h;
				if(h > 0) h--;
			}
		}	
	}
};


#endif