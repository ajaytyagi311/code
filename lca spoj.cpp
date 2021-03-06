#include<bits/stdc++.h>
#define int long long
#define db(x) (cerr << #x << ": " << (x) << '\n')
const int INF = 1000000007;
using namespace std;
vector<vector<int>> up;
vector<int> d;
void clearUp(){
    up.clear();
    up.resize(1001, vector<int>(21));
    d.clear();
}
void fillUp(int m){
    for(int j{1}; j <= 20; ++j){
        for(int i{1}; i <= m; ++i){
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}
void dfs(int a, vector<vector<int>>& adj, int depth){
    d[a] = depth;
    for(auto x: adj[a])
        dfs(x, adj, depth + 1);
}
int lca(int a, int b){
    if(d[a] < d[b])
        swap(a, b);
    // now a is deeper
    int diff = d[a] - d[b];
    for(int bit{20}; bit >= 0; --bit){
        if(diff & (1<<bit)){
            a = up[a][bit];
        }
    }
    if(a == b)
        return a;
    assert(d[a] == d[b]);
    for(int bit{20}; bit >= 0; --bit){
        if(up[a][bit] != up[b][bit]){
            a = up[a][bit];
            b = up[b][bit];
        }
    }
    assert(up[a][0] == up[b][0]);
    return up[a][0];
}
int32_t main(){  //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tc;
    cin>>tc;

    for(int i{1}; i <= tc; ++i){
        cout<<"Case "<<i<<":"<<endl;
        clearUp();
        int n;
        cin>>n;
        d.resize(n + 1);
        vector<vector<int>> adj(n + 1);
        for(int i{1}; i <= n; ++i){
            int m;
            cin>>m;
            while(m--){
                int x;
                cin>>x;
                up[x][0] = i;
                adj[i].push_back(x);
            }
            int root = 1;
            while(up[root][0]){
                root = up[root][0];
            }
            dfs(root, adj, 0);
        }
        int q;
        cin>>q;
        while(q--){
            int a, b;
            cin>>a>>b;
            cout<<lca(a, b)<<endl;
        }
    }
    return 0;
}
