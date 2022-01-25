/*
	Definition of the operations of the type ModInt, 
	which are the integers in Z_MOD.

	You may use it in the same way that you use "int" type.
	Complexity:
		Everything is O(1), except for the functions "/" and "pow",
		which are O(log (something)).
*/

template<int MOD>
struct ModInt {
  	unsigned x;
  	ModInt() : x(0) { }
	ModInt(signed sig) : x(sig) {  }
	ModInt(signed long long sig) : x(sig%MOD) { }
	int get() const { return (int)x; }
	ModInt pow(ll p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
	 
 	ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
	ModInt &operator/=(ModInt that) { return (*this) *= that.pow(MOD - 2); }
	 
	ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
	ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
	ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
	bool operator<(ModInt that) const { return x < that.x; }
	friend ostream& operator<<(ostream &os, ModInt a) { os << a.x; return os; }
	friend istream& operator>>(istream &is, ModInt &a) { is >> a.x; return is; }
};
typedef ModInt<1000000007> mint;
template<class T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
