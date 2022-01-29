/*
    Gauss Elimination algorithm to solve linear system of equations.

    Parameters:
        A * ans = b
        "b" comes in the last column of "a" and "A" is the rest 
    
    Return value:
        - It returns 
            - INF if there are infintely many solutions to the system,
            - 0 if there isn't any
            - 1 if there is a unique solution.
        - If there is only one solution, it returns in the vector "ans" this solution
        - If there are infinitely many, in the positions that I have a choice, it returns INF.

    Usage:
        You may use it with any group that is 
        like T = "double", "long double", "ModInt" and etc.

    Complexity: 
        O(min(n,m) * n * m)
*/

const double eps = 1e-9;
const int INF = 1e9+7; 

template<class T>
int gauss (vector<vector<T>> a, vector<T> & ans) {
    int n = (int)a.size(), m = (int)a[0].size() - 1;

    for (int it = 0; it < min(n, m); it++) {
        // Firtly, take the row with largest entry to be the pivot
        int sel = it;
        for (int i = it; i < n; i++) 
            if (abs(a[i][it]) > abs(a[sel][it])) sel = i;
        if (abs(a[sel][it]) < eps) continue;

        // Exchange the rows sel and it
        for (int i = it; i <= m; i++) 
            swap (a[sel][i], a[it][i]);
        
        // Eliminate all entries in the column it
        for (int i = 0; i < n; i++)
            if (i != it) {
                T c = a[i][it] / a[it][it];
                for (int j = it; j <= m; j++)
                    a[i][j] -= a[it][j] * c;
            }
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) 
        if (abs(a[i][i]) > eps) ans[i] = a[i][m] / a[i][i];

    // Check if actually it solves the system
    for (int i = 0; i < n; i++) {
        T sum = 0;
        for (int j = 0; j < m; j++) 
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > eps) return 0;
    }

    for (int i = 0; i < m; i++) 
        if (abs(a[i][i]) < eps) return INF;

    return 1;
}