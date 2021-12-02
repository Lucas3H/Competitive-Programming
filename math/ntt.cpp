/*
    Number Theoretic Transform
    Goal: multiply two polynomials in Z_p, for p prime
    Complexity: O(n * log n)
    Details: be aware that we must find some primitive root for p prime
    p = 998244353 is the most used prime in these cases
*/

namespace NTT {
    const long long MOD = 998244353;
    const long long root = 15311432;
    const long long root_1 = 469870224;
    const long long root_pw = 1 << 23;

    long long fastxp(long long n, long long e){
        long long ans = 1, pwr = n;
        while(e){
            if(e%2)  ans = ans * pwr % MOD;
            e /= 2;
            pwr = pwr * pwr % MOD;
        }
        return ans % MOD;
    }


    void fft(vector<long long> & a, bool invert) {
        long long n = a.size();

        for (long long i = 1, j = 0; i < n; i++) {
            long long bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j) swap(a[i], a[j]);
        }

        for (long long len = 2; len <= n; len <<= 1) {
            long long wlen = invert ? root_1 : root;
            for (long long i = len; i < root_pw; i <<= 1)
                wlen = (long long)(1LL * wlen * wlen % MOD);

            for (long long i = 0; i < n; i += len) {
                long long w = 1;
                for (long long j = 0; j < len / 2; j++) {
                    long long u = a[i+j], v = a[i+j+len/2] * w % MOD;
                    a[i+j] = u + v < MOD ? u + v : u + v - MOD;
                    a[i+j+len/2] = u - v >= 0 ? u - v : u - v + MOD;
                    w = (long long)(1LL * w * wlen % MOD);
                }
            }
        }

        if (invert) {
            long long n_1 = fastxp(n, MOD - 2);
            for (long long & x : a) x = x * n_1 % MOD;
        }
    }
 
    vector<long long> multiply(vector<long long> &a, vector<long long> &b) {
        vector<long long> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        long long sz = a.size() + b.size() - 1, n = 1;
        while (n < sz) n <<= 1;

        fa.resize(n), fb.resize(n);
        fft(fa, 0), fft(fb, 0);
        for (long long i = 0; i < fa.size(); i++) fa[i] = fa[i] * fb[i] % MOD;

        fft(fa, 1);
        fa.resize(sz);
        return fa;
    }
};