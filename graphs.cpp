#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define FastIo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
const ll  MAX=1e6+10, MOD= 1e9+7,INF = 1e14;

namespace graph{
    int dx[]{1,0,-1,0};             // down&right&up&left (Respectively)
    int dy[]{0,1,0,-1};
    int dX[]{0,0,1,-1,1,-1,-1,1};  // east&west&south&north&southEast&northWest&northEast&southWest (Respectively)
    int dY[]{1,-1,0,0,1,-1,1,-1};
    vector<vector<int>> adjlist(MAX);
    vector<vector<int>> adjMat(MAX);
    vector<int> topoSort;
    int vis[MAX],dist[MAX], color[MAX],
    vid=0,Time=1,inTime[10],outTime[10],     // vid trick is essentially used iff you need to do memset on vis array , instead just ++vid
    subTreeSize[MAX],depth[MAX];
    vector<int> children[MAX];
    int up[MAX][LOG]; // up[v][j] is 2^j-th ancestor of v
    int parent[MAX];

    bool isValid(int i,int j){
        return i >= 0 && i < N && j >= 0 && j < M;  // IT'S zero-based
    }
    
    void dfs(int node){
        vis[node]=1;            // if you are using vid instead of memset assign cur vid to vis[node]
        for(int x:adjlist[node]){
            if(!vis[x])
                dfs(x);
        }
    }
    
    int dfsCS(int node){
        // if you are using vid instead of memset assign cur vid to vis[node]
        vis[node]=1;
        int cntr = 1;
        for(int x:adjlist[node]){
            if(!vis[x])
                cntr += dfsCS(x);
        }
        return cntr;
    }
    
    bool dfsBGC(int node , int c){
        //dfsBipartiteGraphColoring
        vis[node] = 1;
        color[node] = c;
        for(int child : adjlist[node]){
            if(!vis[child]){
                bool res = dfsBGC(child , c ^ 1);     // XOR (^_^) changes 0 -> 1 , 1 -> 0
                if(!res)
                    return 0;
            }
            else {
                if (color[node] == color[child])
                    return 0;
            }
        }
        return 1;
    }
    
    void dfsDT(int node,int prevDistance){
        //dfsDistanceForTrees,Its valid but for only Tree graph
        dist[node]+=prevDistance;
        vis[node]=1;
        for(int x:adjlist[node]){
            if(!vis[x])
                dfsDT(x,dist[node]+1);
        }
    }
    
    bool dfsUDGCD(int node,int src){
        //dfs to detect cycles on an undirected graph
        if(vis[node])
            return 1;  //cycle
        vis[node]=1;
        for(int x:adjlist[node]){
            if(x!=src)
                if(dfsUDGCD(x,node))
                    return 1;  //cycle
        }
        return 0;     //not cycle
    }
    
    bool dfsDGCD(int node){
        //  dfs to detect cycles on a directed graph
        vis[node] = 1;
        for(int child : adjlist[node]){
            if(vis[child] == 0){
                bool f = dfsDGCD(child);
                if(f)
                    return 1;
            }
            else{
                if(vis[child]==1)
                    return 1;  //   cycle
            }
        }
        vis[node]=2;    //  dfs is done for it
        return 0;       //  no cycle
    }
    
    int CCnCo(){
        // count connected Components
        memset(vis, 0, sizeof vis);     // use vid instead for a better complexity
        int components = 0;
        for(int i = 1;i<=N;++i){
            if(!vis[i]){
                ++components;
                dfs(i);
            }
        }
        return components;
    }
    
    void dfsAjMat(int node,int parent =-1) {
    // dfs for AdjMatrix
    // to detect cycles here uncomment next 2 lines and erase condition !vis[i] in the below forloop
    //    if (vis[node])  //  It's a cycle
    //        return true;
        vis[node] = 1;
        for (int i = 0; i < N; ++i)
            if (i != parent && adjMat[node][i] && !vis[i])     //there is an edge between us then go traversing it
                dfsAjMat(i, node);
    }
    
    void dfsLIMST(int node){
        //dfs to know a node lies in my subTree or not (given u,v vertices)
        //at the end If inTime[u] < inTime[v] and outTime[u] > outTime[v] then the child lies in the subtree of the parent.
        inTime[node]=Time++;
        vis[node]=1;        // or use vid trick
        for(int child : adjlist[node]){
            if(!vis[child])
                dfsLIMST(child);
        }
        outTime[node] = Time++;
    }
    
    void dfstopo(int node){
        //topologicalValidSortDFS
        vis[node]=1;                // or use vid trick
        for(int x:adjlist[node]){
            if(!vis[x])
                dfs(x);
        }
        topoSort.emplace_back(node);  //this node has no vis children
    }
    
    bool ka(){
        // khanAlgoFroTopoSort
        priority_queue<int,vi,greater<int>>pq;  // TO SORT OUTPUT ASC
        vi adj[MAX];
        int inDeg[MAX]{};
        for(int i = 1;i<=N;i++)
            if(inDeg[i]==0)
                pq.push(i);
        int node;
        while (!pq.empty()){
            node = pq.top();
            pq.pop();
            topoSort.pb(node);
            for(int x:adj[node]){
                inDeg[x]--;
                if(inDeg[x] == 0)
                    pq.push(x);
            }
        }
        return topoSort.size() == N;    // all nodes are here ?
    }
    
    int dfsSTS(int node){
        // Calculating subtree size using dfs in O(N)
        vis[node] = 1;
        int curSize = 1;
        for(auto &child:adjlist[node]){
            if(!vis[child]) {
                curSize += dfsSTS(child);
            }
        }
        subTreeSize[node] = curSize;
        return curSize;
    }
    void pure_bfs(int src){
        // basic bfs
        // for multi src bfs get src's positions in a vector,
        // then do the same code below but in loop to finish all src's
        queue<int>que;
        que.emplace(src);
        depth[src] = 0;
        int curFront;
        vid++;
        while (!que.empty()){
            curFront = que.front();
            que.pop();
            for(auto &child:adjlist[curFront]){
                if(vis[child]!=vid){
                    que.emplace(child);
                    depth[child] = depth[curFront] + 1;
                    vis[child] = vid;
                }
            }
        }
    }
    
    void bfsSSSP(int src){
        // another way for bfs
        queue<int>que;
        que.emplace(src);
        vis[src] = vid;
        depth[src] = 0;
        int curFront,curSize,distance = 0;
        vid++;
        while (!que.empty()){
            curSize = que.size();  // this variable maintains current lv elements cntr
            while (curSize--){
                curFront = que.front();
                que.pop();
                for(auto &child:adjlist[curFront]){
                    if(vis[child]!=vid){
                        que.emplace(child);
                        depth[child] = distance + 1;
                        vis[child] = vid;
                    }
                }
            }
            distance++;
        }
    }
    
    void lpt(){
        // to get the longest path in a tree
        // we bfs from node 1 and maintains the furthest node in the code
        // then bfs from the furthest node
        // bfsSSSP(1);
        // int lpt = bfsSSSP(furthest);     // this bfs should return last distance achieved
    }
    
    /****************************************************************************************************/
    class DSU{
    public:
        //rankByNode maintains cntr of nodes/people in a certain group and to get it,
        // correctly you should qyery for the parent of a certain node then query rankbynode for this parent of group
        // rank maintains the height of the imaginary tree
        vi parent,rank,rankByNode;
        DSU(int n){
            parent.resize(n+1);
            rank.resize(n+1,1);
            rankByNode.resize(n+1,1);
            for(int i=1;i<=n;++i) parent[i] = i;
        }
        int find(int U) {
            return (parent[U] == U) ?
                   U : parent[U] = find(parent[U]);
        }
        bool join(int x, int y) {
            x = find(x), y = find(y);
            if(x == y)  return false; 
            if(rank[x] > rank[y])
                swap(x,y);
            parent[x] = y;  
            rankByNode[y] += rankByNode[x];
            rankByNode[x] = y;
            if(rank[x]==rank[y])
                rank[y]++;
            return true;
        }
        bool sameSet(int x,int y){
            return find(x) == find(y);
        }
        vector<vector<int>> connectedComponents(){
            int n = sz(parent);
            vector<vector<int>> list(n);
            for(int i=0;i<n;++i)
                list[find(i)].pb(i);
            return list;
        }
    };
    /****************************************************************************************************/
    struct Edge{
        int from,to,weight,index;
        bool del;   // to get kth MST
        Edge(int from,int to,int weight,int index):
        from(from),to(to),weight(weight),index(index),del(false){}
        //sort edges ascend
        bool operator < (const Edge &edge)
        const{
            return weight > edge.weight;            // for priority queue use > ,for array use <  ,all to sort ascend
        }
        bool operator == (const Edge & e) const {
            return ( from == e.from && to == e.to && weight == e.weight);
        }
    };
    P<ll,V<Edge>> KruskalMST(V<Edge> &EdgeList,int siz){
        //Time comp E.log(E) || E.log(V)
            DSU unionFind(siz);
            V<Edge>FinalGraph;
            ll mstCost = 0;
            PQ<Edge>pqSortedEdge;       //ascend
           for(int i = 0;i<EdgeList.size();++i){
                if(!EdgeList[i].del)        // for 2nd mst    
                pqSortedEdge.push(EdgeList[i]);
            }
            while (!pqSortedEdge.empty()){
                Edge e = pqSortedEdge.top();
                pqSortedEdge.pop();
            if(unionFind.union_set(e.from,e.to)){
                    mstCost+=e.weight;
                    FinalGraph.pb(e);
                }
            }
            if(FinalGraph.size() == siz-1)   //isTree?
                return {mstCost,FinalGraph};
        
            //else        //Not a tree ->> DisConnected Graph
            return {INF,V<Edge>()}; //sz of returned Graph is zero
        }
        pair<ll,vector<Edge>> get_2nd_MST(pair<ll,vector<Edge>>&_1stMST,vector<Edge>&edgeList){
            ll secondCost = INF;
            pair<ll,vector<Edge>> curMST;   // cost , edges of the tree
            for(int i=0;i<_1stMST.second.size();++i){
                // we can here instead of brute-force deleting all edges we should only delete edges with the same cost of the current edges or more
                edgeList[_1stMST.second[i].index].del=1;
                pair<ll,vector<Edge>> tmpMST = KruskalMST(edgeList,N);
                if(tmpMST.first < secondCost){
                    secondCost = tmpMST.first;
                    tie(tmpMST) = curMST;
                }
                //back the removed edge
                edgeList[_1stMST.second[i].index].del=0;
            }
            return curMST;
        }
    
    /****************************************************************************************************/

    void dfsts(int a) {
        // tree ancestors dfs
        for(int b : children[a]) {
            depth[b] = depth[a] + 1;
            up[b][0] = a; // a is parent of b
            for(int j = 1; j < LOG; j++) {
                up[b][j] = up[up[b][j-1]][j-1];
            }
            dfsts(b);
        }
    }
    
    int get_lca(int a, int b) { // O(log(N))
        if(depth[a] < depth[b]) {
            swap(a, b);
        }
        // 1) Get same depth.
        int k = depth[a] - depth[b];
        for(int j = LOG - 1; j >= 0; j--) {
            if(k & (1 << j)) {
                a = up[a][j]; // parent of a
            }
        }
        // 2) if b was ancestor of a then now a==b
        if(a == b) {
            return a;
        }
        // 3) move both a and b with powers of two
        for(int j = LOG - 1; j >= 0; j--) {
            if(up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }

    void binaryLifting(){
        //TreeAncestor code
        // problem : a tree of size N, rooted at 0
        // answer Q queries
        // given u and k, find kthAncestor of u
        for(int i=0;i<N;++i) parent[i] =i;
        int logg = 0;
        while((1 << logg) <= N) {
            logg++;
        }
        // up[v][j] is 2^j -th ancestor of node v
        for(int v = 0; v < N; v++) {
            up[v][0] = parent[v];
            if(v != 0) {
                depth[v] = depth[parent[v]] + 1;
            }
            for(int j = 1; j < logg; j++) {
                up[v][j] = up[ up[v][j-1] ][j-1];
            }
        }
    }
    int getKthAncestor(int node, int k) {   // O(log2(N))
        binaryLifting();    // precompute it in the main
        if(depth[node] < k) {
            return -1;
        }
        for(int j = LOG - 1; j >= 0; j--) {
            if(k >= (1 << j)) {
                node = up[node][j];
                k -= 1 << j;
            }
        }
        return node;
    }
    // some graphs generator
    vector<pair<int,int>> csg(int n){
        // construct star graph (also its considered as a tree) -> m-1 edges
        assert(n>1);
        vector<pair<int,int>> graph;
        int idx = 1;
        while (--n){
            graph.emplace_back(1,++idx);
        }
        return graph;
    }
    vector<pair<int,int>> ccg(int n){
        // construct chain graph (also its considered as a tree) -> m-1 edges
        assert(n>1);
        vector<pair<int,int>> graph;
        int idx = 0;
        while(--n){
            graph.emplace_back(idx+1,idx+2),idx++;
        }
        return graph;
    }

}