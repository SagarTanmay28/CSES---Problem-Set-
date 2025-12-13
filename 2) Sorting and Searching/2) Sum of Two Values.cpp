int main(){
    long long n,x;
    cin >> n >> x;
 
    vector<long long> v;
    for(long long i=0;i<n;i++){
        long long val;
        cin >> val;
        v.push_back(val);
    }
 
    unordered_map<long long,long long> mp;
    bool flag = false;
    for(long long i=0;i<n;i++){
        long long rem = x - v[i];
        if(rem <= 0) continue;
        if(mp.find(rem) != mp.end()){
            flag = true;
            cout << mp[rem] + 1 << " " << i + 1 << endl;
            break;
        }
        mp[v[i]] = i;
    }
 
    if(flag == false) cout << "IMPOSSIBLE" << endl;
 
}
