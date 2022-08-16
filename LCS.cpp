class LCS {
public:
    int dp[3005][3005]; // according to |s|
    string text1,text2;
    int lcs(int i,int j){  //time : O(N.M)
        if(i == text1.size() || j == text2.size())
            return 0;

        int &ret =  dp[i][j];
        if(ret!=-1)
            return ret;

        if(text1[i] == text2[j])
            return ret = 1+lcs(i+1,j+1);

        int p1 = lcs(i,j+1);
        int p2 = lcs(i+1,j);
        return ret = max(p1,p2);

    }
    int longestCommonSubsequence(string text1, string text2) {
        memset(dp, -1, sizeof(dp));
        this->text1 = text1;
        this->text2 = text2;
        return  lcs(0,0);
    }
    string getLCSWord(){
        string ans;
        int i = 0, j =0;
        while(i <sz(text1)  && j < sz(text2)) {
            // If current character in both the strings are same, then current character is part of LCS
            if(text1[i] == text2[j]){
                ans.push_back(text1[i]);
                i++;
                j++;
            }
              // If current character in X and Y are different & we are moving upwards
            else if(dp[i+1][j] > dp[i][j+1]) i++;
              // If current character in X and Y are different & we are moving leftwards
            else j++;
        }
        return ans;
    }
   // Main TEST code
   /*  
    LCS s;
    string s1,s2;
    cin>>s1 >>s2;
    s.longestCommonSubsequence(s1,s2)<<el;
    cout<<s.getLCSWord();
    */

};
