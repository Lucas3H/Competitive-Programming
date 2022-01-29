/*
    Find all inverses mod m
    Source: https://cp-algorithms.com/algebra/module-inverse.html#toc-tgt-3
*/

const int MOD = 1000001;

int inv[MOD];
void all_inverse(){
	inv[1] = 1;
	for(int i = 2; i < m; ++i)
	    inv[i] = m - (m/i) * inv[m%i] % m;
}
