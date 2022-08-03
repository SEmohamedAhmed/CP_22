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
#define printDS(s) {for(auto ss:s)cout<<ss<<' ';}
#define clrA(v, d) memset(v, d, sizeof(v))      // range {-1,0}
#define clrV(v, d) memset(&v[0], d, sz(v) * sizeof(v[0]))
#define Rev(v) reverse(all(v))
#define sortt(v) sort(all(v))
#define RevSortt(v) sort(all(v),greater<>())
#define ssort(v) stable_sort(all(v))
#define FastIo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); // std:: be3:)
using namespace std;
/*صلوا على النبى*/
const ll  MAX=1e3+5, MOD= 1e9+7,INF = 1e18;
const double EPS=1e-9,PI = acos(-1);;
ll t=1,N,M,K,u,v,C;
/*************************************************/
// problem::https://www.spoj.com/problems/HORRIBLE/
vl arr;    // resize with n
vl tree,lazyProp;    //resize with 4*n
void checkLazyProp(int nodeNum,int st,int end){
    if(lazyProp[nodeNum] != 0){
        tree[nodeNum]+=(end-st+1)*lazyProp[nodeNum];    // range sum
        if(st!=end){
            lazyProp[2*nodeNum]+=lazyProp[nodeNum];
            lazyProp[2*nodeNum+1]+=lazyProp[nodeNum];
        }
        lazyProp[nodeNum] = 0;
    }
}
void build(int nodeNumber,int start,int end){
    // time: O(n.logn)
    checkLazyProp(nodeNumber,start,end);
    if(start == end){
        tree[nodeNumber] = arr[start]; // or end
        return;
    }

    int nodeLeft = 2*nodeNumber,nodeRight = 2*nodeNumber+1;

    build(nodeLeft,start,(start+end) /2);
    build(nodeRight,(start+end)/2+1 ,end);

    tree[nodeNumber] = tree[nodeRight]+tree[nodeLeft];
}
void update(int nodeNumber,int start,int end,
            int St_targetIndex,int end_targetIndex
            ,ll newValue){
    checkLazyProp(nodeNumber,start,end);
    int nodeLeft = 2*nodeNumber,nodeRight = 2*nodeNumber+1;

    if(start>=St_targetIndex && end<=end_targetIndex){
        tree[nodeNumber] += (end-start+1)*newValue;   // to get sum of this range

        if(start!=end){
            lazyProp[nodeLeft]+=newValue;
            lazyProp[nodeRight]+=newValue;
        }
        return;
    }
    if(St_targetIndex>end || end_targetIndex<start)    // out of the interval
        return;

        update(nodeLeft,start,(start+end)/2,
               St_targetIndex,end_targetIndex,newValue);
        update(nodeRight,((start+end)/2)+1,end,
               St_targetIndex,end_targetIndex,newValue);

    tree[nodeNumber] = tree[nodeRight]+tree[nodeLeft];
}

ll query(int nodeNumber,int start,int end,int x,int y){
    checkLazyProp(nodeNumber,start,end);

    if(start>=x && end<=y){
        return tree[nodeNumber];
    }
    if(x>end || y<start)   
        return 0;     
    return query(2*nodeNumber,start,(start+end)/2,x,y)    // left
            +query(2*nodeNumber+1,(start+end)/2+1,end,x,y);   // right
}
/*************************************************/
void solve() {
    cin>>N>>M;
    arr.resize(N,0);
    tree.resize(4*N);
    lazyProp.resize(4*N,0);
    build(1,0,N-1);
    while (M--){
        int p,q;
        cin>>u>>p>>q;
        p--,q--;
        if(u == 1){
            cout << query(1,0,N-1,p,q)<<el;
        }else if(u==0){
            cin>>v;
            update(1,0,N-1,p,q,v);
        }
    }
}
int main() {
FastIo
cin>>t;
while (t--)
{solve();}
//cout<<"\nFinished\n";
return 0;
}
