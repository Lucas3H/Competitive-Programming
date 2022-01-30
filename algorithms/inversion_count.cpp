/*
    Inversion count using merge sort

    Description: count the number of inversions in a given vector

    Complexity: O(n log n)
*/

template<typename T>
long long merge_sort(vector<T> & v){
    if(v.size() <= 1) return 0;
    long long n = v.size(), ans = 0;
    vector<T> l(v.begin(), v.begin() + n / 2), r(v.begin() + n / 2, v.end());
    v.clear();
    ans += merge_sort(l) + merge_sort(r);

    long long il = 0, ir = 0;
    while(il < l.size() || ir < r.size()){
        if(il == l.size()) v.push_back(r[ir++]);
        else if(ir == r.size()) v.push_back(l[il++]);
        else {
            if(l[il] < r[ir]) v.push_back(l[il++]);
            else v.push_back(r[ir++]), ans += l.size() - il;
        }
    } 
    return ans;
}
