#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define pi pair<int,int>
#define rep0(i,N) for(int i=0;i<N;++i)
#define rep(i,N) for(int i=1;i<=N;++i)
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
    map<pi,char>mp{{{1,0},'D'},{{0,1},'R'},{{-1,0},'U'},{{0,-1},'L'}};     // UDLR way
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
/****************************************************************************************************/
    int _0_1_BFS(int a,int b,int c,int d){
        //we apply this function if our edge weights can only be 0 and x (x >= 0) ? yes !
        int ans = 0;
        rep0(i,N+1)
        rep0(j,M+1)
        dist[i][j] = INT_MAX;
        deque <pi> deque1;
        dist[a][b] = 0;
        deque1.push_back({a,b});
        while (!deque1.empty()){
            int curX = deque1.front().F,curY = deque1.front().S;
            if(curX == c && curY == d){
            ans = dist[c][d];
            break;
        }
        deque1.pop_front();
        rep0(i,8){
        int weight;
        if(codeToDir[grid[curX][curY]-'0'] == i)   
            weight=0;
        else
            weight=1;

        int xx = dirX[i] + curX,yy = curY + dirY[i];
        if(is_Valid(xx,yy)){
        // checking for the optimal distance
        if (dist[xx][yy] > weight + dist[curX][curY]){
        dist[xx][yy] = weight + dist[curX][curY];
        if (weight == 0)
        deque1.push_front({xx,yy});
        else
        deque1.push_back({xx,yy});
        }}}}
        return ans;
        }
        // in main
        /*
        This problem can also be solved by Dijkstra,
        but the time complexity will be O(E + V Log V)
        ,whereas by BFS it will be O(V+E).
        */
        cin>>N>>M;
        rep(i,N)
        rep(j,M)
        cin>>grid[i][j];
        cin>>K;
        while (K--) {
        int start_x, start_y, end_x, end_y;
        cin >> start_x >> start_y >> end_x >> end_y;
        cout << _0_1_BFS(start_x, start_y, end_x, end_y) << el;
}
/****************************************************************************************************/
    void lpt(){
        // to get the longest path in a tree-graph
        // we bfs-dfs from node 1 and maintains the furthest node in the code
        // then bfs-dfs from the furthest node
        // bfsSSSP(1);
        // int lpt = bfsSSSP(furthest);     // this bfs should return last distance achieved
    }
/****************************************************************************************************/
    
        vector<int> parent; // to get the path
        bool dijkstra(int src,vector<vector<pair<int,ll>>> &graph){     // basic dijkstra , to get cheapest path from src to destination
            int n = graph.size();
            vector<ll> dist(n,INF);
            parent.resize(n,-1);
            vector<bool> vis(n);
            priority_queue<pair<ll,int>>nextToVisit; // cost,toNode
            nextToVisit.emplace(0,src);
            dist[src] = 0;
            while (!nextToVisit.empty()){
                int u = nextToVisit.top().second;
                nextToVisit.pop();
                if(vis[u])continue;
                vis[u] = 1;
                for(auto &next :graph[u]){
                    ll cost = next.second;
                    int v = next.first;
                    if(dist[u] + cost < dist[v]){
                        parent[v] = u;
                        dist[v] = dist[u] + cost;
                        nextToVisit.emplace(-dist[v],v);
                    }
                }
            }
            if(dist[N] >= INF){ // can reach destination
                cout << -1;
                return 0;
            }
            return 1;
            /*rep(i,n-1)cout <<dist[i] << el;
            rep(i,n-1)cout <<parent[i] << el;*/
        }
        void printPath(int source = 1, int dest = N)
        {
            stack<int> st;
            int final = dest;
            while(parent[dest] != source){
                dest = parent[dest];
                st.push(dest);
            }
            cout<<source<<" ";
            while(!st.empty()){
                cout<<st.top()<<" ";
                st.pop();
            }
            cout<<final<<el;
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
    
    void dfsts(int a=1) {     // call this function with root node (1) , for preprocessing, then you can use LCA fn
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
        int k = depth[a] - depth[b];
        for(int j = LOG - 1; j >= 0; j--) {
            if(k & (1 << j)) {
                a = up[a][j]; // parent of a
            }
        }
        if(a == b) {
            return a;
        }
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
        /***************************************************************************************************************************************/
            struct LCA {            // another LCA sol using segtree -> build in O(N) & query in O(N.log.N)
            vector<int> height, euler, first, segtree;
            vector<bool> visited;
            int n;

            LCA(vector<vector<int>> &adj, int root = 0) {
                n = adj.size();
                height.resize(n);
                first.resize(n);
                euler.reserve(n * 2);
                visited.assign(n, false);
                dfs(adj, root);
                int m = euler.size();
                segtree.resize(m * 4);
                build(1, 0, m - 1);
            }

            void dfs(vector<vector<int>> &adj, int node, int h = 0) {
                visited[node] = true;
                height[node] = h;
                first[node] = euler.size();
                euler.push_back(node);
                for (auto to : adj[node]) {
                    if (!visited[to]) {
                        dfs(adj, to, h + 1);
                        euler.push_back(node);
                    }
                }
            }

            void build(int node, int b, int e) {
                if (b == e) {
                    segtree[node] = euler[b];
                } else {
                    int mid = (b + e) / 2;
                    build(node << 1, b, mid);
                    build(node << 1 | 1, mid + 1, e);
                    int l = segtree[node << 1], r = segtree[node << 1 | 1];
                    segtree[node] = (height[l] < height[r]) ? l : r;
                }
            }

            int query(int node, int b, int e, int L, int R) {
                if (b > R || e < L)
                    return -1;
                if (b >= L && e <= R)
                    return segtree[node];
                int mid = (b + e) >> 1;

                int left = query(node << 1, b, mid, L, R);
                int right = query(node << 1 | 1, mid + 1, e, L, R);
                if (left == -1) return right;
                if (right == -1) return left;
                return height[left] < height[right] ? left : right;
            }

            int lca(int u, int v) {
                int left = first[u], right = first[v];
                if (left > right)
                    swap(left, right);
                return query(1, 0, euler.size() - 1, left, right);
            }
        };
    /****************************************************************************************************************************************/
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


    /****************************************************************************************************************************************/
         #define MAXV 50
        #define MAXE 200
        struct DirectedEulerGraph {
            int V,ne,last[MAXV],to[MAXE],next[MAXE],cur[MAXV];
            int in[MAXV],out[MAXV];
            int start,end;
            std::vector<int> path;

            DirectedEulerGraph(){}

            void clear(int V_){
                V = V_; ne = 0;
                memset(last,-1,sizeof last);
                memset(in,0,sizeof in);
                memset(out,0,sizeof out);
            }

            void add_edge(int u, int v){
                to[ne] = v; next[ne] = last[u]; last[u] = ne++;
                ++out[u]; ++in[v];
                start = u;
            }

            bool check(){
                int cont = 0,aux = start;
                start = end = -1;

                for(int i = 0;i < V;++i){
                    if(in[i] == out[i]) ++cont;
                    else if(out[i] == in[i] + 1) start = i;
                    else if(in[i] == out[i] + 1) end = i;
                    else return false;
                }

                if(cont == V){
                    start = end = aux;
                    return true;
                }

                return (cont == V - 2 && start != -1 && end != -1);
            }

            bool build(){
                stack<int> st;
                st.push(start);
                memcpy(cur,last,sizeof last);
                path.clear();

                while(!st.empty()){
                    int u = st.top();

                    if(cur[u] == -1){
                        path.push_back(u);
                        st.pop();
                    }else{
                        int v = to[ cur[u] ];
                        cur[u] = next[ cur[u] ];
                        st.push(v);
                    }
                }

                reverse(path.begin(),path.end());
                return path.size() == ne + 1;
            }
        };
      
/****************************************************************************************************************************************/
            class Euler{
            /*
             * Eulerian_Path_undirected is a path in graph that visits every edge exactly once.
             * */
            struct Edge;
            typedef list<Edge>::iterator iter;
            struct Edge{
                int next_vertex;
                iter reverse_edge;
                Edge(int next_vertex):next_vertex(next_vertex){ }
            };
            static const int max_vertices = 6;
            int num_vertices;
            list<Edge> adj[max_vertices];		// adjacency list
            vector<int> path;

            void find_path(int v){
                while(adj[v].size() > 0){
                    int vn = adj[v].front().next_vertex;
                    adj[vn].erase(adj[v].front().reverse_edge);
                    adj[v].pop_front();
                    find_path(vn);
                }
                path.push_back(v);
            }

            void add_edge(int a, int b){
                adj[a].push_front(Edge(b));
                iter ita = adj[a].begin();
                adj[b].push_front(Edge(a));
                iter itb = adj[b].begin();
                ita->reverse_edge = itb;
                itb->reverse_edge = ita;
            }
            void solve(){
                add_edge(1,2);
                add_edge(2,3);
                add_edge(3,4);
                add_edge(4,5);
                find_path(1);
                reverse(all(path));
                //print(path)
            }
        };
    /****************************************************************************************************************************************/

        int diameter_tree(int s,const vector<vector<int>>&Graph){
            queue<int> Q;
            Q.push(s);
            const int  MAX = 100;
            bool vis[MAX];
            int prev[MAX];
            memset(vis,0,sizeof(vis));
            vis[s] = true;      // or use vid trick
            prev[s] = -1;
            int ans = s;
            while(!Q.empty()){
                int aux = Q.front();
                Q.pop();
                ans = aux;
                for(int i=Graph[aux].size()-1;i>=0;--i){
                    int v = Graph[aux][i];
                    if(vis[v]) continue;
                    vis[v] = 1;
                    Q.push(v);
                    prev[v] = aux;
                }
            }
            return ans;
        }
    /****************************************************************************************************************************************/
        // Kosaraju algo for detecting SCC in O(V+E)
        // src:: https://www.topcoder.com/thrive/articles/kosarajus-algorithm-for-strongly-connected-components
        #define MAX_N 20001
        int n, m;
        struct Node {
            vector < int > adj;
            vector < int > rev_adj;
        };
        Node g[MAX_N];
        stack < int > S;
        bool visited[MAX_N];
        int component[MAX_N];
        vector < int > components[MAX_N];
        int numComponents;
        void dfs_1(int x) {
            visited[x] = true;
            for (int i = 0; i < g[x].adj.size(); i++) {
                if (!visited[g[x].adj[i]]) dfs_1(g[x].adj[i]);
            }
            S.push(x);
        }
        void dfs_2(int x) {
            printf("%d ", x);
            component[x] = numComponents;
            components[numComponents].push_back(x);
            visited[x] = true;
            for (int i = 0; i < g[x].rev_adj.size(); i++) {
                if (!visited[g[x].rev_adj[i]]) dfs_2(g[x].rev_adj[i]);
            }
        }
        void Kosaraju() {
            for (int i = 0; i < n; i++)
                if (!visited[i]) dfs_1(i);
            for (int i = 0; i < n; i++)
                visited[i] = false;
            while (!S.empty()) {
                int v = S.top();
                S.pop();
                if (!visited[v]) {
                    printf("Component %d: ", numComponents);
                    dfs_2(v);
                    numComponents++;
                    printf("\n");
                }
            }
        }
        int main() {
            cin >> n >> m;
            int a, b;
            while (m--) {
                cin >> a >> b;
                g[a].adj.push_back(b);
                g[b].rev_adj.push_back(a);
            }
            Kosaraju();
            printf("Total number of components: %d\n", numComponents);
            return 0;
        }
    /******************************************************/
        // Tarjan algo for detecting SCC in O(V+E)
        // Tarjan algo for detecting SCC in O(V+E)
        #define MAX 10  // # of vertices
        int n, m, id, rep[MAX];
        vector<int> graph[MAX], brdg[MAX];
        int dfn[MAX], low[MAX], timer;
        bool in_st[MAX];
        stack<int> st;
        void tarjan(int node, int par = 1) {
        dfn[node] = low[node] = ++timer;
        in_st[node] = 1;
        st.push(node);
        for (auto to : graph[node]) {
            if (to == par) continue;
            if (dfn[to] == 0) {
                tarjan(to, node);
                low[node] = min(low[node], low[to]);
            }
            if (in_st[to])
                low[node] = min(low[node], dfn[to]);
        }
        if (dfn[node] == low[node]) {
            ++id;
            while(true) {
                int cur = st.top();
                cout << cur << " ";
                st.pop();
                in_st[cur] = 0;
                rep[cur] = id;
                if (cur == node)
                    break;
            }
            cout <<el;
        }
        }
        void meen(){
            int a,b;
            cin >> n >> m;
            while (m--) cin >> a >> b,graph[a].push_back(b),graph[b].push_back(a);
            tarjan(1);   // start from any node , changes will be in the order of printing SCC 
        }

    /****************************************************************************************************************************************/
