#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define forr(i,a,b) for(ll i=a;i<b;i++)


const ll N = 1e4 + 5;
const ll INF = 2e5 + 5;

vector <vector<ll>> adj_list(N);
ll graph[N][N];

map<ll, ll> value;
map<ll, ll> parent;
map<ll, bool> vis;

void Dijkstra(ll n,ll s,ll d, ofstream &outfile)
{
    for (ll i = 0; i <= n; i++)  value[i] = INF;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    pq.push({0, s});
    parent[s] = s;
    value[s] = 0;

    while (!pq.empty())
    {
        ll curr = pq.top().second;
        pq.pop();

        if (vis[curr]) continue;
        vis[curr] = true;

        forr(i,0,adj_list[curr].size())
        {
            ll neighbour=adj_list[curr][i];
            if(! vis[neighbour] && value[neighbour]>value[curr]+graph[curr][neighbour])
            {
                value[neighbour]=value[curr]+graph[curr][neighbour];

                pq.push({value[neighbour],neighbour});
                parent[neighbour]=curr;
            }
        }
    }


    ll child=d;
    vector<ll> v;
    while(child!=s)
    {
        v.push_back(child);
        child=parent[child];
    }
    v.push_back(child);

    cout<<"Dijkstra Algorithm:\n"<<value[d]<<endl;
    outfile<<"Dijkstra Algorithm:\n"<<value[d]<<endl;
    for(ll i=v.size()-1;i>=0;i--)
    {
        cout<<v[i]-1;
        outfile<<v[i]-1;
        if(i!=0) cout<<" -> ";
        if(i!=0) outfile<<" -> ";
    }
}

int main() {

    ifstream infile("Dijkstra_input.txt");
    ofstream outfile("Dijkstra_output.txt");


    if(!infile)
    {
        cout<<"Could not open the Input File";
        return 0;
    }



    ll n, m,s,d;
    infile>>n>>m;

    for (ll i = 1; i < m+1; i++)
    {
        ll u, v, w;
        infile >> u >> v >> w;
        u++;
        v++;

        adj_list[u].push_back(v);
        graph[u][v] = abs(w);
    }
    infile>>s>>d;

    Dijkstra(n,s+1,d+1,outfile);


    infile.close();
    outfile.close();
}
