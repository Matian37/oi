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

const int base = 200001;

vector<int> graph[base];
bool color[base];
bool visited[base], visited2[base];
int n, m;

void DFS(int v, bool c)
{
    color[v] = c;
    visited[v] = true;

    for (int w : graph[v])
        if (!visited[w])
            DFS(w, !c);
}

bool checkDFS(int v)
{
    visited2[v] = true;

    bool f = !color[v], s = color[v];

    if (f == false)
    {
        for (int w : graph[v])
        {
            if (!color[w]) 
            {
                f = true; 
                break;
            }
        }
    }

    if (s == false)
    {
        for (int w : graph[v])
        {
            if (color[w]) 
            {
                s = true; 
                break;
            }
        }
    }

    if (!s || !f)
        return false;
    
    for (int w : graph[v])
    {   
        if (!visited2[w])
            if (!checkDFS(w))
                return false;
    }
    return true;
}

void solve()
{
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            DFS(i, false);
    
    for (int i = 1; i <= n; i++)
    {
        if (!visited2[i])
        {
            if (!checkDFS(i))
            {
                cout << "NIE";
                return;
            }
        }
    }

    cout << "TAK\n";

    for (int i = 1; i <= n; i++)
        cout << (color[i] ? 'S' : 'K') << '\n';
}

void readGraph()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    readGraph();
    solve();
}