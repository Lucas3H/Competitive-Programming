struct compare {
    bool operator() (const pair<int,int> &lhs, const pair<int,int> &rhs) const{
         return (lhs.second-lhs.first > rhs.second-rhs.first);
    }
};

set<pair<int,int>, compare> myset;
