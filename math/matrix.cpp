/*
	Fast-Use library for matrix operations
*/

typedef vector<vector<double>> matrix;

/*
	Gauss-Jordan elimination algorithm to find the inverse of a given matrix A
	
	Matrix:
		- It returns in matrix b the inverse of a, if it exists.
	
	Return value:
		- Return true if the inverse exists and 0 otherwise

	Complexity:
		- O(n^3)
*/
template<class T>
bool inverse (vector<vector<T>> a, vector<vector<T>> & b) {
    int n = (int)a.size();
    b.resize(n);
    for(int i = 0; i < n; i++) b[i].resize(n), b[i][i] = 1;

    for (int it = 0; it < n; it++) {
        // Firtly, take the row with largest entry to be the pivot
        int sel = it;
        for (int i = it; i < n; i++) 
            if (abs(a[i][it]) > abs(a[sel][it])) sel = i;
        if (abs(a[sel][it]) < eps) return false;

        for (int i = 0; i < n; i++) 
            swap (a[sel][i], a[it][i]), swap(b[sel][i], b[it][i]);

        T c = a[it][it];
        for (int i = 0; i < n; i++)	
        	a[it][i] /= c, b[it][i] /= c;

        // Eliminate all entries in the column it
        for (int i = 0; i < n; i++)	
            if (i != it) {
                c = a[i][it];
                for (int j = 0; j < n; j++)
                    a[i][j] -= a[it][j] * c, b[i][j] -= b[it][j] * c;
            }
    }
	return true;
}

/*
	Determinant
*/
template<class T>
T determinant(vector<vector<T>> a) {
    int n = (int)a.size();
    T ret = 1;

    for (int it = 0; it < n; it++) {
        // Firtly, take the row with largest entry to be the pivot
        int sel = it;
        for (int i = it; i < n; i++) 
            if (abs(a[i][it]) > abs(a[sel][it])) sel = i;
        if (abs(a[sel][it]) < eps) return false;

        for (int i = 0; i < n; i++) 
            swap (a[sel][i], a[it][i]);

        T c = a[it][it];
        for (int i = 0; i < n; i++)	
        	a[it][i] /= c;

        ret *= c;

        // Eliminate all entries in the column it
        for (int i = 0; i < n; i++)	
            if (i != it) {
                c = a[i][it];
                for (int j = 0; j < n; j++)
                    a[i][j] -= a[it][j] * c;
            }
    }
	return true;
}

template<class T>
vector<vector<T>> operator * (vector<vector<T>> & a, vector<vector<T>> & b){
	int n = a.size(), m = b[0].size();
	if(a[0].size() != b.size()) assert(0);
	vector<vector<T>> ret;
	ret.resize(a.size());

	for(int i = 0; i < n; i++){
		ret[i].resize(m, 0);
		for(int j = 0; j < m; j++){
			for(int k = 0; k < b.size(); k++){
				ret[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return ret;
}

template<class T>
vector<vector<T>> operator + (vector<vector<T>> & a, vector<vector<T>> & b){
	int n = a.size(), m = a[0].size();
	if(n != b.size() || m != b[0].size()) assert(0);
	vector<vector<T>> ret(n)
	for(int i = 0; i < n; i++){
		ret[i].resize(m, 0);
		for(int j = 0; j < m; j++) ret[i][j] = a[i][j] + b[i][j];
	}
	return ret;
}

template<class T>
vector<vector<T>> operator - (vector<vector<T>> & a, vector<vector<T>> & b){
	int n = a.size(), m = a[0].size();
	if(n != b.size() || m != b[0].size()) assert(0);
	vector<vector<T>> ret(n)
	for(int i = 0; i < n; i++){
		ret[i].resize(m, 0);
		for(int j = 0; j < m; j++) ret[i][j] = a[i][j] - b[i][j];
	}
	return ret;
}