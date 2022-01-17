/*
    Binary Indexed Tree

    Structure to make prefix queries and point updates

    Complexity:
        BIT()         : O(log n)
        update        : O(log n)
        query         : O(log n)
        lower_bound() : O(log n)
*/

struct BIT{
    vector<int> bit;
    int n;

    BIT(int tam = 0){n = tam, bit.resize(n + 1, 0);}
    BIT(vector<int> & a){
        n = (int)a.size(), bit.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) update(i, a[i-1]);
    }
    BIT(int a[], int tam){
        n = tam, bit.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) update(i, a[i-1]);
    } 
    
    inline int op(int x, int y) {return x + y;}
    
    void update(int i, int val){
        for(; i <= n; i += i & (-i)) bit[i] = op(bit[i], val);
    }

    int query(int i){
        int sum = 0;
        for(; i > 0; i -= i & (-i)) sum = op(sum, bit[i]);
        return sum;
    }

    /*O(log n)*/
    int lower_bound(int v){
	    int sum = 0, pos = 0;
        for(int i = (int)ceil(log2(n)); i >= 0; i--){
            if(pos + (1 << i) < n && op(sum, bit[pos + (1 << i)]) < v){
                sum = op(sum, bit[pos + (1 << i)]);
                pos += (1 << i);
            }
        }
	    return pos + 1; 
    } 
};