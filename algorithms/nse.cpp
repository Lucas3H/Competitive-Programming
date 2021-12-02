/*
    Next "something" element
    something = smaller, greater, smaller or equal, greater or equal

    For instance in case "smaller": if v = {4, 8, 5, 2, 25}
    Then nse = {2, 5, 2, -1, -1}

    Complexity: O(n)
*/

template<class Operator>
vector<int> nse(const vector<int> & v, Operator op){
    int n = (int)v.size();
    vector<int> ret(n, n);
    stack<int> s;

    for(int i = 0; i < n; i++){
        while(!s.empty() && op(v[s.top()], v[i])){
            ret[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }

    return ret;
}

int main(){
    vector<int> v = {0 5 7 3 9 10 1 6 13 7};
    vector<int> l;
    l = nse(v, std::greater()); // Next smaller element
    for(auto x : l) cout << x << " ";
    cout << endl;

    l = nse(v, std::greater_equal()); // Next smaller or equal element
    for(auto x : l) cout << x << " ";
    cout << endl;

    l = nse(v, std::less()); // Next greater element
    for(auto x : l) cout << x << " ";
    cout << endl;

    l = nse(v, std::less_equal()); // Next greater or equal element
    for(auto x : l) cout << x << " ";
    cout << endl;
}