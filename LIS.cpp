// returns LIS data
vi LIS_n_LOGn(const vector<int> &nums) {
    // longest (strictly)increasing subsequence
    vector<int> ans;
    int n=nums.size();
    for(int i=0; i<n; i++) {
        auto it = lower_bound(all(ans), nums[i]);
        if(it == ans.end()){
            ans.push_back(nums[i]);
        }
        else {
            *it = nums[i];
        }
    }
    return ans;
    // test fun in main
    /*
        vi arr{1,2,3,2,2,2,2,3,7,15,21,156,516,351};
        vi ans = LIS_n_LOGn(arr);
        printDS(ans)
     */
}
/**************************************************************************************************************************************************/
vi arr;
int mem[MAX][MAX];
int LIS_N_square(int idx,int prevIdx){
    if(idx == sz(seq))
        return 0;
    auto &ret = mem[idx][prevIdx];
    if(ret!=-1)
        return ret;
    int p1 = LIS(idx+1,prevIdx),p2=0;    //leave
    if(prevIdx >= sz(arr) || arr[prevIdx] < arr[idx])   // strictly increasing 
        p2 = 1+LIS(idx+1,idx);
    return ret = max(p1,p2);
}

/**************************************************************************************************************************************************/



