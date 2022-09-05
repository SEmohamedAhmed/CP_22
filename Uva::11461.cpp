#include <bits/stdc++.h>
#include <cstring>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define all(v) v.begin(),v.end()
#define mkp make_pair
#define el '\n'
#define V vector
#define vi V<int>
#define vvi V<vi>
#define vl V<ll>
#define vul V<ull>
#define vb V<bool>
#define pb push_back
#define eb emplace_back
#define pf push_front
#define vc vector<char>
#define vs vector<string>
#define P pair
#define pd pair<double,double>
#define pl pair<ll,ll>
#define pi pair<int,int>
#define tiii tuple<int,int,int>
#define vpi V<pair<int,int>>
#define vpl V<pair<ll,ll>>
#define F first
#define S second
#define OO 2000000000
#define rep(i,n) for(int i=1;i<=n;++i)  //[1:N]
#define rep0(i,n) for(int i=0;i<n;++i)  //[0:N-1]
#define sz(v) (int)v.size()            // unsigned fails in some cases
#define fixed(n) fixed<<setprecision(n)
#define ones(x) __builtin_popcountll(x)
#define printDS(s) {for(auto ss:s)cout<<ss<<' ';}
#define Print2DGrid(arr,N,M) rep0(i,N){rep0(j,M)cout<<arr[i][j]<< "";cout<<el;}
#define cin2d(g,N,M) rep0(i,N)rep0(j,M)cin>>g[i][j];
#define cin1d(a) for(auto &I:a)cin>>I;
#define clrA(v, d) memset(v, d, sizeof(v));      // range {-1,0,0x3f}
#define clrV(v, d) memset(&v[0], d, sz(v) * sizeof(v[0]))
#define Rev(v) reverse(all(v))
#define sortt(v) sort(all(v))
#define RevSortt(v) sort(all(v),greater<>())
#define ssort(v) stable_sort(all(v))
#define FastIo ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define fillArrIncreasing(arr,n) iota(all(arr),n);
#define BigInt __int128
#define printBigInt(num) {string str; do {int digit = num % 10;str = to_string(digit) + str;num = (num - digit) / 10;} while (num != 0);cout << str;}
#define subsequencesCnt(n) (1ll<<n)       // minus 1 to ignore empty subsequence
#define subarraysCnt(n) 1ll* n * (n + 1) / 2
#define sumFirstNEvenNumbers(n) 1ll* n * (n + 1)
#define sumFirstNOddNumbers(n) 1ll* n * n
// صلوا على النبى
const ll  MAX=1e4+100, MOD= 1e9+7,INF = 1e14,LOG = 14;
const double EPS=1e-7,PI = acos(-1);
ll T=1,N,M,K;
/*************************************************/
ordered_set s;
void pre(){
rep(i,317)s.insert(i*i);    // put here sqrt(max(b)), to gurantee that all sqrt numbers will be generated
}
/*************************************************/
void solve() {
"TODO::codeReviewPlease:D";
while(cin>>N>>M&&N){
cout << s.order_of_key(M+1) - s.order_of_key(N) << el;
}
}
signed main()
{
pre();
FastIo
//cin>>T;
while (T--)
{solve();}
return 0;
}
