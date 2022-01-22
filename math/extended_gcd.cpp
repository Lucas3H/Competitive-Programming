/*
    Extended Euclidean algorithm
    Complexity: O(log(max(a, b)))
*/

int gcdExtended(int a, int b, int &x, int &y) { 
    int g; 
    if (a == 0) x = 0, y = 1, g = b;
    else{
        g = gcdExtended(b%a, a, x, y);
        int aux = x;
        x = y - (b / a) * x, y = aux;
    }
    return g; 
} 