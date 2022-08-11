/*
author @ MrMody
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
#define pb push_back
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
#define OO (int)1e9
#define rep(i,n) for(int i=1;i<=n;++i)
#define rep0(i,n) for(int i=0;i<n;++i)
#define per(i,n) for(int i=n;i>-1;--i)
#define sz(v) (unsigned int)v.size()
#define fixed(n) fixed<<setprecision(n)
#define ones(x) __builtin_popcountll(x)
#define printDS(s) {for(auto ss:s)cout<<ss<<' ';}
#define Print2DGrid(arr,N,M) rep0(i,N){rep0(j,M)cout<<arr[i][j]<< " ";cout<<el;}
#define cin2d(g) rep0(i,N)rep0(j,M)cin>>g[i][j];
#define clrA(v, d) memset(v, d, sizeof(v))      // range {-1,0,0x3f}
#define clrV(v, d) memset(&v[0], d, sz(v) * sizeof(v[0]))
#define Rev(v) reverse(all(v))
#define sortt(v) sort(all(v))
#define RevSortt(v) sort(all(v),greater<>())
#define ssort(v) stable_sort(all(v))
#define FastIo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); // std:: be3:)
using namespace std;
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ull, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// صلوا على النبى
const ll  MAX=2e1+5, MOD= 1e9+7,INF = 1e14,LOG = 18;
const double EPS=1e-9,PI = acos(-1);
ll t=1,N,M,K,u=0,v,c;
/*************************************************/
string n1,n2;
map<string ,int>nameToID;

class New_DSU{
int nn;
public:
vi parent,rank;
New_DSU(int n){
nn = n;
parent.resize(n+1);
rank.resize(n+1,1);
rep(i,n)
parent[i] = i;
}
int find(int U) {
return (parent[U] == U) ?
U : parent[U] = find(parent[U]);
}
bool join(int x, int y) {
x = find(x), y = find(y);
if(x == y)
return false;
if(rank[x] < rank[y])
swap(x, y);
parent[y] = x;
rank[x] += rank[y];     //it maintains number of nodes in the current network
return true;
}
};
/*************************************************/
void solve() {
// TODO
nameToID.clear();
cin>>N;
int ID = 0;
New_DSU dsu(2*N+10);    // assume all lines has new 2 people then ID will reach 2*N
rep(i,N){
cin>>n1>>n2;
auto &itr1 = nameToID[n1],&itr2 =  nameToID[n2];
if(itr1 == 0)itr1 =++ID;
if(itr2 == 0)itr2 =++ID;
dsu.join(itr1,itr2);
cout << dsu.rank[dsu.find(itr1)] << el;
}
}
int main() {
FastIo
cin>>t;
while (t--)
{solve();}
return 0;
}
