#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double


const ll N = 1001;
const ll INF = 2e5 + 5;
vector<vector<ll>> cost( N , vector<ll> (N, INF));
vector<vector<ll>> pre;




void Matrix_Multiplication(ll n)
{
    for(ll i=1;i<=n;i++) cost[i][i] =0;
    pre=cost;

    for(ll count=1;count<=n;count++)
    {
        vector<vector<ll>> dist( n+1 , vector<ll> (n+1, INF));
        for(ll i=1;i<=n;i++)
        {
            for(ll j=1;j<=n;j++)
            {
                for(ll k=1;k<=n;k++)
                {
                    if(pre[i][k]!=INF && cost[k][j]!=INF)
                        dist[i][j] = min(dist[i][j],pre[i][k]+cost[k][j]);
                }
            }
        }
        pre=dist;
    }


    cout<<"Shortest distance matrix"<<endl;
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=n;j++)
            if(pre[i][j]==INF) cout<<"INF ";
            else  cout<<pre[i][j]<<" ";

        cout<<endl;
    }
}




int main() {
    ll n, m;
    cin >> n >> m;


    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        ld w;
        cin >> u >> v >> w;

        cost[u][v]=w;
    }

    Matrix_Multiplication(n);
}
