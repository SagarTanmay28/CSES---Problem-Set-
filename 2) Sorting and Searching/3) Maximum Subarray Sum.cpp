#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
 
int main(){
    long long n;
    cin >> n;
    
    vector<long long> nums;
    for(long long i=0;i<n;i++){
        long long num;
        cin >> num;
        nums.push_back(num);
    }
 
    long long ans = INT_MIN;
    long long sum = 0;
    for(long long x : nums){
        sum += x;
        ans = max(ans,sum);
        if(sum < 0) sum = 0;
    }
    
    cout << ans;
    
 
}
