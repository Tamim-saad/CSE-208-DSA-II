#include<bits/stdc++.h>
using namespace std;


#define ll long long
#define endl "\n"
#define vec vector<ll>
#define forr(i,a,b) for(ll i=a;i<b;i++)



struct Edge
{
    ll u,v,w;

    Edge() {}
    Edge(ll u,ll v,ll w)
    {
        this->u=u;
        this->v=v;
        this->w=w;
    }
};


struct Node
{
    ll value;
    ll parent=-1;
    ll rank=0;
};

const ll N=2e+5;
Edge edge[N];
Node node[N];


struct edge_sort
{
    bool operator()(Edge const& e1, Edge const& e2)
    {
        return e1.w > e2.w;
    }
};


ll FindParent(ll u)
{
    if(node[u].parent==-1) return u;
    return node[u].parent=FindParent(node[u].parent);
}

void Union(ll u, ll v)
{
    if(node[u].rank>=node[v].rank)   node[v].parent=u;
    else if(node[u].rank<node[v].rank)    node[u].parent=v;
    if(node[u].rank==node[v].rank)   node[u].rank++;
}



int main()
{

    ifstream infile("kruskal_input.txt");
    ofstream outfile("kruskal_output.txt");


    if(!infile)
    {
        cout<<"Could not open the Input File";
        return 0;
    }


    ll i,j=0,u,v,w,n,m,ans=0,flag=1;
    infile>>n>>m;


    vector<pair<ll,ll>> vans;
    priority_queue<Edge, vector<Edge>, edge_sort> pq;

    forr(i,0,m)
    {
        infile>>u>>v>>w;
        u++;
        v++;

        node[u].value=u;
        node[v].value=v;

        pq.push(Edge(u,v,w));
    }




    while (!pq.empty())
    {
        Edge e=pq.top();

        ll pu=FindParent(e.u);
        ll pv=FindParent(e.v);

        pq.pop();

        if(pu!=pv)
        {
            ans+=e.w;
            vans.push_back(make_pair(e.u,e.v));

            Union(pu,pv);
        }
    }


    cout<<"Kruskal's Algorithm:\nTotal weight = "<<ans<<endl;
    outfile<<"Kruskal's Algorithm:\nTotal weight = "<<ans<<endl;


    forr(i,0,vans.size())
    {
        cout<<vans[i].first-1<<" "<<vans[i].second-1<<endl;
        outfile<<vans[i].first-1<<" "<<vans[i].second-1<<endl;
    }

    infile.close();
    outfile.close();

}
