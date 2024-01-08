#include<bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
const int INF = 2e5 + 5;

int graph[N][N];

void prims(int n) {
    map<int, int> value;
    map<int, int> parent;
    map<int, bool> visited;

    for (int i = 1; i <= n; i++) {
        value[i] = INF;
        visited[i] = false;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, 1});
    parent[1] = -1;
    value[1] = 0;

    while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        for (int i = 1; i <= n; i++) {
            if (!visited[i] && graph[curr][i] > 0 && graph[curr][i] < value[i]) {
                parent[i] = curr;
                value[i] = graph[curr][i];
                pq.push({value[i], i});
            }
        }
    }

    int ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += graph[i][parent[i]];
    }

    cout<<"Prims Algorithm:\nTotal weight = "<<ans<<endl;
    cout<<"ROOT Node: "<<0<<endl;
    for (int i = 2; i <= n; i++) {
        cout << i - 1 << ' ' << parent[i] - 1 << '\n';
    }
}

int main() {

    ifstream infile("prims_input.txt");
    ofstream outfile("prims_output.txt");


    if(!infile)
    {
        cout<<"Could not open the Input File";
        return 0;
    }


    int n, m;
    infile >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        infile >> u >> v >> w;
        graph[u + 1][v + 1] = w;
        graph[v + 1][u + 1] = w;
    }

    prims(n);

    infile.close();
    outfile.close();

    return 0;
}
