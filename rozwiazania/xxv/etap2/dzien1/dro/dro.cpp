//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000
#define ii pair<int,int>
#define pll pair<long long, long long>
#define pul pair<unsigned long long, unsigned long long>
#define Tak cout << "TAK" << '\n';
#define Nie cout << "NIE" << '\n';

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

using namespace std;

vector<int> g[50005], reversed[50005], sccGraph[50005];

int scc[50005], sccSize[50005];

stack<int> postorder;

bool visited[50005][4];

void postOrder(int v)
{
    visited[v][0] = true;

    for (int w : g[v])
        if (!visited[w][0])
            postOrder(w);
    postorder.push(v);
}

void setSCC(int token, int v)
{
    visited[v][1] = true;
    scc[v] = token;
    sccSize[token]++;

    for (int w : reversed[v])
        if (!visited[w][1])
            setSCC(token, w);
}

void createGraph(int v)
{
    visited[v][2] = true;

    for (int w : g[v])
    {
        if (scc[v] != scc[w])
            sccGraph[scc[v]].push_back(scc[w]);
        if (!visited[w][2])
            createGraph(w);
    }
}

void initGraph(int n)
{
    for (int i = 1; i <= n; i++)
        if (!visited[i][2])
            createGraph(i);
}

int sajz[50005];

int sizeDFS(int v)
{
    visited[v][3] = true;
    sajz[v] = sccSize[v];

    for (int w : sccGraph[v])
        if (!visited[w][3])
            sajz[v] += sizeDFS(w);
        else
            sajz[v] += sajz[w];
    return sajz[v];
}

void initSize(int token)
{
    for (int i = 1; i <= token; i++)
        if (!visited[i][3])
            sizeDFS(i);
}


int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        reversed[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
        if (!visited[i][0])
            postOrder(i);
    
    int token = 0;

    while (!postorder.empty())
    {
        auto acc = postorder.top();
        postorder.pop();

        if (scc[acc] != 0)
            continue;
        setSCC(++token, acc);
    }
    
    initGraph(n);
    initSize(token);

    for (int i = 1; i <= n; i++)
    {
        cout << sajz[scc[i]] - 1 << '\n';
    }
}