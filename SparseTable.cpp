/*
  author @ Mohamed_Ahmed
  3-Aug-2022
*/

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
#define mpii map<P<int,int>,int>
#define mii map<int,int>
#define PQ priority_queue
#define Q queue
#define MS multiset
#define pb push_back
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
#define OO (int)1e9
#define rep(i,n) for(int i=1;i<=n;++i)
#define rep0(i,n) for(int i=0;i<n;++i)
#define per(i,n) for(int i=n;i>-1;--i)
#define sz(v) (unsigned int)v.size()
#define fixed(n) fixed<<setprecision(n)
#define printDS(s) {for(auto ss:s)cout<<ss<<' ';}
#define Print2DGrid(arr,N,M) rep0(i,N){rep0(j,M)cout<<arr[i][j];cout<<el;}
#define clrA(v, d) memset(v, d, sizeof(v))      // range {-1,0,0x3f}
#define clrV(v, d) memset(&v[0], d, sz(v) * sizeof(v[0]))
#define Rev(v) reverse(all(v))
#define sortt(v) sort(all(v))
#define RevSortt(v) sort(all(v),greater<>())
#define ssort(v) stable_sort(all(v))
#define FastIo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); // std:: be3:)
using namespace std;
// صلوا على النبى
const ll  MAX=1e2+5, MOD= 1e9+7,INF = 1e18,LOG = 10;// replace LOG with log(N)
const double EPS=1e-9,PI = acos(-1);
ll t=1,N,M,K,u,v,C;
/*************************************************/
/*
 * if you just need (Big number of InfoQueries)
 * [sum,min,max,gcd,and,or,lcm,xor] of a given range
 * query[L,R] USE SPARSE TABLE!
 * Below is the implementation_by_Errichto
 */
int a[MAX];
int m[MAX][LOG]; // m[i][j] is minimum among a[i..i+2^j-1]
int closest_log[MAX];
int query(int L, int R) {      // O(1)
    int length = R - L + 1;
    int k = closest_log[length];
    return m[L][k]& m[R-(1<<k)+1][k];     // [min,max,gcd,and,or,lcm]
}
// the following fn is only for range sum query
ll RSQ(int L, int R) {      // O(LOG) ~ O(1)
    ll sum = 0;
    for (int j = LOG; j >= 0; j--) {
        if ((1 << j) <= R - L + 1) {
            sum += m[L][j];
            L += 1 << j;
        }
    }
    return sum;
}
int bruteForceSol(int L, int R){
    assert(L>=0&&L<N&&R>=0&&R<N);
    int ans = a[L];                         // put here a proper value that won't affect our ans
    for(int i=L+1;i<=R&&i<N;++i){
        ans = (ans&a[i]);                 // here change op to [min,max,gcd,and,or,lcm]
    }
    return ans;
}
/*************************************************/
void solve() {
    int q;
    cin >> N >> q;
    closest_log[1] = 0;
    for (int i = 2; i <= N; i++) {
        closest_log[i] = closest_log[i / 2] + 1;
    }
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        m[i][0] = a[i];
    }
    // build the table  O(N*log(N))
    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i + (1 << k) - 1 < N; i++) {
            m[i][k] = (m[i][k - 1] & m[i + (1 << (k - 1))][k - 1]);
            // here change op to [sum,min,max,gcd,and,or,lcm]
        }
    }
    // ans queries
    for (int i = 0; i < q; i++) {
        int L, R;
        scanf("%d%d",&L,&R);
        if(L>R)swap(L,R);
        --L,--R;   //if given ranges are 1-based to convert to 0-based
        int ans = query(L, R);
        printf("SparseTableSol [from %d to  %d] is %d\n", L, R, ans);
        printf("bruteForceSol [from %d to  %d] is %d\n", L, R, bruteForceSol(L,R));
    }
}

int main() {
//FastIo
//cin>>t;
while (t--)
{solve();}
//cout<<"\nFinished\n";
return 0;
}
