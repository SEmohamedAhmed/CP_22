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
V<vc>g;
vvi dist; // we can replace this as we maintain shortest path in a variable "distance", but we still need 2d vis array not to visit cells repeatedly
int dx[]{1,0,-1,0};    
int dy[]{0,1,0,-1};
map<pi,pi>parent;
map<pi,char>mp{{{1,0},'D'},{{0,1},'R'},{{-1,0},'U'},{{0,-1},'L'}};
bool valid(int i,int j){return i>=0&&i<N&&j>=0&&j<M;}
int bfs(pi start,pi end){
queue<pi>q;
q.emplace(start);
rep0(i,N)rep0(j,M)dist[i][j] = -1;
dist[start.F][start.S] = 0;
int distance = 0,si = sz(q);
for(;!q.empty();si = sz(q)){
while(si--){
int x = q.front().F , y = q.front().S;
q.pop();
rep0(i,4){
int X = dx[i] + x,Y = dy[i]+y;
if(valid(X,Y) && g[X][Y]!='#' &&dist[X][Y] == -1){
dist[X][Y] = dist[x][y]+1,q.emplace(X,Y);
parent[{X,Y}]=mkp(x,y);
if(X == end.F && Y == end.S){
goto endIt;
}}}}}
endIt:
return dist[end.F][end.S];
}
vpi getPath(pi start,pi end){
vpi path;
pi cur = {end.F,end.S};
// go till reaching the starting point
while (1){
    path.emplace_back(cur.F,cur.S);
    if(cur == start)break;
    cur = parent[cur];
}
Rev(path);
return path;
}
string getPathIn_UDLR_way(pi start,pi end){
//    this map a cell to its parent
//    map<pi,pi>parent;
vpi path =  getPath(start,end);
string ans {""};
rep0(i,sz(path)-1){
rep0(j,4){
if(path[i].F+dx[j] == path[i+1].F && path[i].S+dy[j] == path[i+1].S){
ans+=mp[{dx[j],dy[j]}];
break;
}}}
return ans;
}
/*************************************************/
void solve() {
// TODO
cin>>N>>M;
g.resize(N,vc(M));
dist.resize(N,vi(M));
pi start,end;
rep0(i,N)rep0(j,M){
cin>>g[i][j];
if(g[i][j] == 'A')start = {i,j};
else if(g[i][j] == 'B')end = {i,j};
}
int shortestPath =  bfs(start,end);

if(shortestPath >0){
cout << "YES\n"<<shortestPath<<el;
string ans = getPathIn_UDLR_way(start,end);
cout << ans;
}else cout << "NO";
}
int main() {
FastIo
//cin>>t;
while (t--)
{solve();}
return 0;
}
// problem src : https://cses.fi/problemset/task/1193
// Thanks to our instructor Dr.Mostafa Saad
