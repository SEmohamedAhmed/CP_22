/**
* Min insertions to make a string a palindrome
* https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
*/
class Solution {
public:
string s1;
int mem[505][505];
int minInsertionsToBePalindrome(int i,int j){
if(i>=j)
return 0;
auto &itr = mem[i][j];
if(itr!=-1)
return itr;
// by edit distance algorithm
if(s1[i]==s1[j])
return itr = minInsertionsToBePalindrome(i+1,j-1);
int p1 = 1 + minInsertionsToBePalindrome(i+1,j);
int p3 =  1 + minInsertionsToBePalindrome(i,j-1); //insert before cur index
return itr = min(p1,p3);
}

int minInsertions(string s) {
clrA(mem,-1);
this->s1=s;
return minInsertionsToBePalindrome(0, sz(s1)-1);
}
};
/**************************************************************************************************************************************************************/
int memory[MAX][MAX];
  vector<int> rows, cols;
int mcm(int start_idx=0, int end_idx=sz(rows)-1) {	// O(N^3) time
    if (start_idx == end_idx)
        return 0;	// a single matrix: no multiplication
    auto &ret = memory[start_idx][end_idx];
    if (ret != -1)
        return ret;
    ret = INT_MAX;
    for (int k = start_idx; k < end_idx; k++) { // < NOT <=
        int blocks_mult = rows[start_idx] * cols[k] * cols[end_idx];
        int sub1 = mcm(start_idx, k);
        int sub2 = mcm(k + 1, end_idx);
        int total_k = blocks_mult + sub1 + sub2;
        ret = min(ret, total_k);
    }
    return ret;
}
/**************************************************************************************************************************************************************/
