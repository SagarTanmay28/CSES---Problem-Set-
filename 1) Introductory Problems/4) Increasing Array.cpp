#include<iostream>
#include<vector>
#include<algorithm>
 
using namespace std;
int main(){
    long long n;
    cin >> n;
    if(n==1){
        cout << 0;
        return 0;
    }
    vector<long long> nums;
    for(int i=0;i<n;i++){
        long long x;
        cin >> x;
        nums.push_back(x);
    }
    long long count = 0;
    int i = 0;
    int j = 1;
    
    while(j<n){
        if(nums[j]>nums[i]){
            i++;
            j++; 
            continue;
        }
        else{
            count += (nums[i]-nums[j]);
            nums[j] = nums[i];
        }
        i++;
        j++;
    }
    cout <<  count;
}
