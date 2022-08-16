    #include <bits/stdc++.h>
    #define sz(v) (unsigned int)v.size()
    #define el '\n'
    #define all(v) v.begin(),v.end()
    #define ll long long
  
    void sortString_L_T(int l,int r,string &str){
        //--l,--r;  //uncomment if l&r are zero-based
        if(l>r)
        swap(l,r);
        sort(str.begin()+l,str.begin()+r+1);
    }
    void reverseString_L_T(int l,int r,string &str){
        // --l,--r;//uncomment if l&r are zero-based
        if(l>r)swap(l,r);
        reverse(str.begin()+l,str.begin()+r+1);
    }
    string sortString_fast(string &str){
        string ans;
        int freq[26]{};     // max chars
        for(int i=0;i<str.size();++i){
            freq[tolower(str[i])-'a']++;
        }
        for(int i=0;i<26;++i)
            if(freq[i])
                for(int j=0;i<freq[i];++j)
                    ans.pb(char('a'+i));
        return ans;
    }
    /*************************************************************************************************************/
    // src :: https://github.com/jaehyunp/stanfordacm/blob/master/code/KMP.cc
    /*
     * Problem : Find all occurrences of the pattern string b within the string a
     * Algo : KMP
     * time -> O(n + m)
    */
    void BPA(string& b, vector<int>& arr){
        //buildPatternArray
        arr = vi(b.length());
        int k = -2;
        for(int i = 0; i < b.length(); i++) {
            while(k >= -1 && b[k+1] != b[i])
                k = (k == -1) ? -2 : arr[k];
            arr[i] = ++k;
        }
    }
    bool kmp(string& a, string& b)
    {
        vector<int> arr;
        BPA(b, arr);
        int k = -1,matchCnt = 0;
        for(int i = 0; i < a.length(); i++) {
            while(k >= -1 && b[k+1] != a[i])
                k = (k == -1) ? -2 : arr[k];
            k++;
            if(k == b.length() - 1) {
                cout << "A Pattern is MATCHED Here -> " << i-k << ": " <<
                a.substr(i-k, b.length()) << el; // zero-based ya basha hna :D      //here we print to be sure we get a pattern
                matchCnt++;
                k = (k == -1) ? -2 : arr[k];
            }
        }
        if(matchCnt > 0)
            return 1;
        return 0;
    }
      /*************************************************************************************************************/
       string s;
      bool isPalindrome(int i,int j){
            if(i>=j)return true;
            if(s[i]!=s[j])return false;
            //Case : s[i]==s[j]
            return isPalindrome(i+1,j-1);
        }
      /*************************************************************************************************************/
      // src :: gfg
      struct Node{
          unordered_map<char,Node*>mp;
      };
      ll distinctSubstrCntr(string &s){
          int cnt = 0;
          Node *root = new Node();
          for(int i=0;i<s.length();i++)
          {
              Node*curr=root;
              for(int j=i;j<s.length();j++){
                  if(curr->mp.find(s[j])==curr->mp.end()){  
                      curr->mp[s[j]]=new Node();
                      cnt++;
                  }
                  curr=curr->mp[s[j]];
              }
          }
          return cnt+1;
      }
      ll countAllSubstring(string s){
          return (sz(s) * (sz(s)+1)) / 2;
      }
      /*************************************************************************************************************/
      // src :: https://www.geeksforgeeks.org/trie-insert-and-search/
      // src :: https://www.geeksforgeeks.org/trie-delete/

      struct Trie {
          // index is -1, unless it is a leaf node[eof a word in the trie dictionary]
          int index;
          Trie* child[26];
          Trie(){
              for (int i = 0; i < 26; i++)
                  child[i] = 0;
              index = -1;
          }
      };
      bool trieSearch(struct Trie* root, string key)
      {
          struct Trie* tmp = root;
          for (int i = 0; i < key.length(); i++) {
              int index = key[i] - 'a';
              if (!tmp->child[index])
                  return false;
              tmp = tmp->child[index];
          }
          return (tmp != 0 && tmp->index!=-1);
      }
      void insert(Trie* root, string str, int idx){
          Trie* node = root;
          char cur;
          for (int i = 0; i < str.size(); i++) {
              cur = str[i] - 'a';
              if (!node->child[cur])
                  node->child[cur] = new Trie();
              node = node->child[cur];
          }
          node->index = idx;
      }

      bool goTrie(Trie* node, vector<string> arr){
          if (node == 0)
              return 0;
          for (int i = 0; i < 26; i++) {
              if (node->child[i] != 0) {
                  if (node->child[i]->index != -1)
                      cout << arr[node->child[i]->index] << el;
                  goTrie(node->child[i], arr);
              }
          }
          return 1;
      }

      void sort(vector<string> arr){
          // print trie content in lexicographically sorted order
          Trie* root = new Trie();
          for (int i = 0; i < sz(arr); i++)
              insert(root, arr[i], i);
          goTrie(root, arr);
      }
      bool isEmpty(Trie* root)
      {
          for (int i = 0; i < 26; i++)
              if (root->child[i])
                  return 0;
          return 1;
      }

      // Recursive function to delete a "key" from given Trie
      Trie* remove(Trie* root, string key, int depth = 0)
      {
          if (!root)
              return 0;
          if (depth == key.size()) {
              if (root->index!=-1)
                  root->index = 1;
              if (isEmpty(root)) {
                  delete root;
                  root = 0;
              }
              return root;
          }
          int index = key[depth] - 'a';
          root->child[index] = remove(root->child[index], key, depth + 1);
          if (isEmpty(root) && root->index == -1) {
              delete root;
              root = 0;
          }
          return root;
      }
      /*************************************************************************************************************/
        // helper function takes a line of list of +ve & -ve int numbers and put it in a list
        vector<ll> readLineToList(string &line){
          vector<ll> lisT;
          int i=0,siz = sz(line);
          bool isNegative = 0;
          while (i<siz){
              isNegative = 0;
              while (i<siz&&line[i]==' ')++i; // got to next int
              string curNum="";
              if(line[i]=='-')isNegative=1,i++;
              while (i<siz&&line[i]!=' ')
                  curNum+=line[i++];
              ll num = stoi(curNum);            // convert string to int , stoi may fail in big numbers
              if(isNegative)num*=-1;
              lisT.pb(num);  
          }
          return lisT;
      }
      /*************************************************************************************************************/
        // mancharAlgo is mainly used to get longest palindrome in a string
        #define MAX_size 20
        int manchar[MAX_size * 2];
        string convertToNewString(const string &s) {
            string newString = "@";
            for (int i = 0; i < sz(s); i++)
                newString += "#" + s.substr(i, 1);
            newString += "#$";
            return newString;
        }

        string mancharAlgo(const string &s) {
            // O(N) time
            string Q = convertToNewString(s);
            int c = 0, r = 0;
            for (int i = 1; i < Q.size() - 1; i++) {
                    int iMirror = c - (i - c);
                    if(r > i) {
                        manchar[i] = min(r - i, manchar[iMirror]);
                    }
                    while (Q[i + 1 + manchar[i]] == Q[i - 1 - manchar[i]]){
                        manchar[i]++;
                    }
                    if (i + manchar[i] > r) {
                        c = i;
                        r = i + manchar[i];
                    }
            }
            int maxPalindrome = 0;
            int centerIndex = 0;
            for (int i = 1; i < Q.size() - 1; i++) {

                if (manchar[i] > maxPalindrome) {
                    maxPalindrome = manchar[i];
                    centerIndex = i;
                }
            }

                    cout << maxPalindrome << "\n";
                    return s.substr( (centerIndex - 1 - maxPalindrome) / 2, maxPalindrome);
                }
                void checkAlgo(){
                    string ar{"aaaaaaaaaaaaaaabbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbb"};
                    cout <<   mancharAlgo(ar);
                }
        /*************************************************************************************************************/

                                                        // SOME NOTES : 
          // It takes one line from a file and put it in a string
        string str;
        char arr[];
        while (getline(cin,str)){}
        // for UVA to get a line and put it in char array
        while(gets(arr)) {}
        // string for printf 
        printf("%s",str.c_str()); 
        // char arr
         printf("%s",arr); 
        /* facts about creating palindromes arrays
         * we have 2 types of palindromes
         * 1- even length
         * 2- odd length
         * for EVEN : all elements in the array must have even-frequency
         * for ODD :  all elements in the array must have even-frequency ,EXCEPT one element
         * */
      /*************************************************************************************************************/
