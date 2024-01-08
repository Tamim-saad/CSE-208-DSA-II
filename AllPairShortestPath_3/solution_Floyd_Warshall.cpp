#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double


const ll N = 1001;
const ll INF = 2e5 + 5;
ld dist[N][N];


void Floyd_Warshall(ll n)
{
    for(ll k=1;k<=n;k++)
    {
        for(ll i=1;i<=n;i++)
        {
            for(ll j=1;j<=n;j++)
            {
                if(i!=k && j!=k)
                {
                    dist[i][j] =min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }

    cout<<"Shortest distance matrix"<<endl;
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=n;j++)
            if(dist[i][j]==INF) cout<<"INF ";
            else cout<<dist[i][j]<<" ";

        cout<<endl;
    }


}

int main() {
    ll n, m;
    cin >> n >> m;

    for(ll i=0;i<=n;i++)
        for(ll j=0;j<=n;j++)
        {
            if(i==j) dist[i][j]=0;
            else dist[i][j]=INF;
        }



    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        ld w;
        cin >> u >> v >> w;

        dist[u][v]=w;
    }

    Floyd_Warshall(n);
}
