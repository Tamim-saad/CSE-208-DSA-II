#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define eb emplace_back
#define vec vector<ll>
#define forr(i, a, b) for (ll i = a; i < b; i++)

const ll INF = 1e9+9;

//--------------------------------------------------------------
struct Graph
{
public:
    ll V;
    vector<vec> adj_list;

    Graph();
    Graph(ll vertices) : V(vertices)
    {
        adj_list.resize(V, vec(V, INF));
    }

    void addEdge(ll u, ll v, ll w)
    {
        adj_list[u][v] =w;
        adj_list[v][u] =w;
    }
};

//--------------------------------------------------------------
Graph Random_Graph(ll V)
{
    Graph G(V);
    srand(time(0));

    forr(i, 0, V)  forr(j, i + 1, V)
    {
            ll w = rand() % 151 + 50; //[50, 200]
            G.addEdge(i, j, w);
    }
    return G;
}

//--------------------------------------------------------------
ll Calculate_route_cost(const vec& tour, const Graph& G)
{
    ll l = 0;
    forr(i, 0, tour.size() - 1)
        l += G.adj_list[tour[i]][tour[i + 1]];

    l+=G.adj_list[tour[tour.size() - 1]][tour[0]];
    return l;
}


//--------------------------------------------------------------
ll Exact_TSP(const Graph& G)
{
    ll n = G.V;
    vector<vec> dp(1 << n, vec(n, INF));

    dp[1][0] = 0;

    forr(mask,1,(1 << n))
    {
        forr(u,0,n)
        {
            if (mask & (1 << u))
            {
                forr(v,0,n)  if ((mask & (1 << v)) && u != v)
                {
                        dp[mask][u] = min(dp[mask][u], dp[mask ^ (1 << u)][v] + G.adj_list[v][u]);
                }
            }
        }
    }

    ll final_mask = (1 << n) - 1;
    ll min_len = INF;

    forr(u,1,n)
        min_len = min(min_len, dp[final_mask][u] + G.adj_list[u][0]);

    return min_len;
}

//--------------------------------------------------------------

vector<pair<ll, ll>> MST_By_Prims(const Graph& G)
{
    ll n = G.V;
    map<ll, ll> value;
    map<ll, ll> par;
    map<ll, bool> vis;

    vector<pair<ll, ll>> mst;

    forr(i,1,n+1)
    {
        value[i] = INF;
        vis[i] = false;
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    pq.push({0, 1});
    par[1] = -1;
    value[1] = 0;

    while (!pq.empty())
    {
        ll curr = pq.top().second;
        pq.pop();

        if (vis[curr]) continue;
        vis[curr] = true;

        forr(i,1,n+1)  if (!vis[i] && G.adj_list[curr][i] > 0 && G.adj_list[curr][i] < value[i])
        {
                par[i] = curr;
                value[i] = G.adj_list[curr][i];
                pq.push({value[i], i});
        }
    }

    forr(i,2,n+1)
        mst.push_back({par[i], i});

    return mst;
}
//--------------------------------------------------------------
void dfs(ll u, const Graph& G, vector<bool>& vis, vec& tour)
{
    tour.eb(u);
    vis[u] = true;

    forr(v, 0, G.V)
    if (vis[v]==false && G.adj_list[u][v] < INF)
            dfs(v, G, vis, tour);
}
//--------------------------------------------------------------
vec Approximation_TSP(const Graph& G)
{
    ll n = G.V;
    vec tour;
    vector<bool> visited(n, false);

    vector<pair<ll, ll>> mst=MST_By_Prims(G);

    Graph newG(n);
    //newG.V=n;

    for(auto x:mst)
    {
        ll u=x.first;
        ll v=x.second;
        ll w=G.adj_list[u][v];
        newG.addEdge(u,v,w);
    }




    dfs(1, newG, visited, tour);
    tour.eb(0);

    return tour;
}
//-------------------------------------------------------------
int main()
{
    ll n; cin >> n;

    forr(i, 1, n + 1)
    {
        ll v = 20;
        Graph G = Random_Graph(v);

        ll Optimal_Len = Exact_TSP(G);
        vec Approx_Tour = Approximation_TSP(G);
        ll Approx_Len = Calculate_route_cost(Approx_Tour, G);

        ld ratio = (ld)(Approx_Len) / (ld)Optimal_Len;
        cout << "Test " << i << ": (approx/optimal) Ratio = " << ratio<< endl;
    }

    return 0;
}
