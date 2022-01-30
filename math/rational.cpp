struct rational{
	ll den, num;

	rational(ll a, ll b){
		ll d = __gcd(a, b);
		num = a / d, den = b / d;
	}

	void print(){
		cout << num << "/" << den << endl;
	}

	inline rational operator+(rational a){return rational(num*a.den + a.num*den, a.den*den);}
	inline rational operator-(rational a){return rational(num*a.den - a.num*den, a.den*den);}
	inline rational operator*(rational a){return rational(num*a.num, a.den*den);}
	inline rational operator/(rational a){return rational(num*a.den, a.num*den);}
	inline bool operator<(rational a){return num*a.den < a.num*den;}
	inline bool operator>(rational a){return num*a.den > a.num*den;}
	inline bool operator<=(rational a){return num*a.den <= a.num*den;}
	inline bool operator>=(rational a){return num*a.den >= a.num*den;}
	inline bool operator==(rational a){return (num == a.num && den == a.den) || (num == -a.num && den == -a.den);}
};

int main(){
	ios::sync_with_stdio(false);

	ll a, b, c, d;
	cin >> a >> b >> c >> d;

	rational x = rational(a, b);
	rational y = rational(c, d);
	
	(x + y).print();
	(x - y).print();
	(x * y).print();
	(x / y).print();
}