#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define forr(i,a,b) for(ll i=a;i<b;i++)




const ll N = 1e4 + 5;
const ll INF = 2e5 + 5;

vector <vector<ll>> adj_list(N);
vector<pair<ll,ll>> edge;
ll graph[N][N];

map<ll, ll> value;
map<ll, ll> parent;
map<ll, bool> vis;

void Bellman_Ford(ll n,ll m,ll s,ll d,ofstream &outfile)
{

    for (ll i = 0; i <= n; i++)  value[i] = INF;

    pair<ll,ll> tmp;

    value[s] = 0;
    forr(j,1,n)
    {
        forr(i,0,edge.size())
        {
            ll u=edge[i].first;
            ll v=edge[i].second;

            if(value[v]>value[u]+graph[u][v])
            {
                value[v]=value[u]+graph[u][v];
                parent[v]=u;
            }

        }
    }

    bool negative_cycle=false;
    forr(i,0,edge.size())
    {
        ll u=edge[i].first;
        ll v=edge[i].second;

        if(value[v]>value[u]+graph[u][v])
        {
            negative_cycle=true;
            break;
        }
    }

    if(negative_cycle)
    {
        cout<<"Negative weight cycle present"<<endl;
        outfile<<"Negative weight cycle present"<<endl;
        return;
    }



    ll child=d;

    vector<ll> v;
    while(child!=s)
    {
        v.push_back(child);
        child=parent[child];
    }
    v.push_back(child);

    cout<<"Bellman Ford Algorithm:\n"<<value[d]<<endl;
    outfile<<"Bellman Ford Algorithm:\n"<<value[d]<<endl;

    for(ll i=v.size()-1;i>=0;i--)
    {
        cout<<v[i]-1;
        outfile<<v[i]-1;
        if(i!=0) cout<<" -> ";
        if(i!=0) outfile<<" -> ";
    }
}

int main() {

    ifstream infile("Bellman_Ford_input.txt");
    ofstream outfile("Bellman_Ford_output.txt");


    if(!infile)
    {
        cout<<"Could not open the Input File";
        outfile<<"Could not open the Input File";
        return 0;
    }

    ll n, m,s,d;
    infile >> n >> m;

    for (ll i = 1; i < m+1; i++)
    {
        ll u, v, w;
        infile >> u >> v >> w;
        u++;
        v++;

        edge.push_back({u,v});

        adj_list[u].push_back(v);
        graph[u][v] = w;
    }
    infile>>s>>d;

    Bellman_Ford(n,m,s+1,d+1,outfile);

    infile.close();
    outfile.close();
}
