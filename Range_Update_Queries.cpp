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
const ll  MAX=3e3+5, MOD= 1e9+7,INF = 1e18;
const double EPS=1e-9,PI = acos(-1);
ll t=1,N,M,K,u,v,C;
/*************************************************/
// problem :: https://cses.fi/problemset/task/1651
int n;
vi arr;
vl tree;
void build(){
    // time : O(N)
    // fill leaves of the tree
    for(int i = 0; i < sz(arr);++i){
        tree[n+i] = arr[i];
    }
}
ll rangeQueryUpdate(int nodeNumber,int start,int end,int x,int y,int new_value){
    if(start>=x && end<=y){
        tree[nodeNumber] += new_value;    // update
        return tree[nodeNumber];
    }
    if(x>end || y<start) {
        return 0;
    }
    ll ret = rangeQueryUpdate(2*nodeNumber,start,(start+end)/2,x,y,new_value)    // branch left
            + rangeQueryUpdate(2*nodeNumber+1,(start+end)/2+1,end,x,y,new_value);  // branch right
    return ret + tree[nodeNumber];
}
ll query(int nodeNumber,int start,int end,int x,int y){
    if(start>=x && end<=y){ // in range ?
        return tree[nodeNumber];
    }
    if(x>end || y<start) {  // out of the interval ?
        return 0;
    }
    ll ret = query(2*nodeNumber,start,(start+end)/2,x,y)    // branch left
             + query(2*nodeNumber+1,(start+end)/2+1,end,x,y);  // branch right
    return ret + tree[nodeNumber];
}
void takeQueries(int q){
    while (q--){
        int qt,a,b;
        cin>>qt>>a;
        a--;
        if(qt == 1){
            cin>>b>>u;
            b--;
            rangeQueryUpdate(1,0,n-1,a,b,u);
        }else if(qt == 2){
            cout << query(1,0,n-1,a,a)<<el;
        }
    }
}
 
void mainData(){
    int q;
    cin>>n>>q;
    arr.resize(n);
    for(auto &i:arr)
        cin>>i;
    while (__builtin_popcount(n) != 1)
        n++;
    tree.resize(2*n);
    build();
    takeQueries(q);
}
/*************************************************/
void solve() {
    mainData();
}
int main() {
FastIo
//cin>>t;
while (t--)
{solve();}
//cout<<"\nFinished\n";
return 0;
}
