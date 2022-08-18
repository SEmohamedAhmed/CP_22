#define el '\n'
#define V vector
#define vi V<int>
#define vvi V<vi>
#define rep(i,n) for(int i=1;i<=n;++i)  //[1:N]

/*
    An Example Problem :
    Consider zero array of size n
    Perform the given BigNumber of add Queries operations from index l to r
    Finally print the array after Q Queries
 */
  // solution using prefixSum trick
  void prefSumTrick(int arrSize, int q){
    vector<ll> pre(arrSize,0);
    int l,r,value;
    while(q--){
        cin>>l>>r>>value;
        if(l>r)swap(l,r);
        //l--,r--;    // if 1-based
        pre[a-1] += value;
        pre[b] -= value;
    }
    for(int i = 1;i<arrSize;++i)
        pre[i]+=pre[i-1];
}
/***************************************************/
// 2D prefixSum
int N,M;
cin>>N>>M;
vvi arr(N+1,vi(M+1,0));         //1-based 
rep(i,N)rep(j,M)cin>>arr[i][j];
// accumulate rows
for(int i = 1; i <= N;++i)
    for(int j = 1; j <= M;++j)
        arr[i][j]+=arr[i][j-1];
// accumulate columns
for(int i = 1; i <= M;++i)
    for(int j = 1; j <= N;++j)
        arr[i][j]+=arr[i-1][j];
// solve query sum from (i,j) to (k,l)
int q,i,j,k,l;
cin>>q;
while (q--){
cin>>i>>j>>k>>l;
  cout <<   arr[k][l] - arr[k][j-1] - arr[i-1][l] + arr[i-1][j-1] <<el;
}
/***************************************************/
ll getMaxNthElements(int kth,vl &pref){
    ll ans = 0, n = sz(pref);
    if(kth>0) {
        int range = n - kth;
        ans = pref[n - 1]; // total
        if (range > 0) {
            range--;
            ans -= pref[range];
        }
    }
    return ans;
}
/***************************************************/
// if u r given a square matrix of size N
// then, Main diagonal is at a[x][x], and secondary diagonal is at a[i][j] : i+j = N
/***************************************************/
 // knight coordinates on a chess board
int dx[]{0,-1,-1,1,1,-2,-2,2,2};   
int dy[]{0,-2,2,-2,2,1,-1,1,-1};    
/***************************************************/
//bishop moves
int dx[]{1,-1,-1,1};
int dy[]{1,-1,1,-1};
/***************************************************/
// Balanced brackets instead of using stack blabla...
rep0(i, sz(str))if(str[i] == '(')ans++; else if(str[i] == ')'){ans--;if(ans<0){yes=0;break;}}
/***************************************************/
  // how to get #Palindromes of distinct anagrams(permutation) of a string
void solve() {
  string a;char c; map<char,int>charCnt;
  cin>>N; rep(i,N)cin>>c,charCnt[c]++;
  int isOdd=0; vi allCnt;
  for(auto &mm:charCnt){if(mm.second&1) isOdd++;allCnt.pb(mm.second/2);}
  if(isOdd<=1){
  int sum = accumulate(all(allCnt),0);ll fac = factorial(sum);ll dom = 1;
  for(auto i:allCnt)dom*=factorial(i);cnt = fac/dom; }
  else cnt=0;   // if there are 2 or more char that has odd #ocurrences then we can not build a plindrom string
  cout<<cnt<<el;}
/***************************************************/
