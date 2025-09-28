//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'
#define min3(x, y, z) min(x, min(y, z))
#define max3(x, y, z) max(x, max(y, z))

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

struct info
{
    int v, c;
    bool did;
};

vector<pair<int,int>> g[5005]; 
int clo[5005];
int n, m;

struct compare
{
    bool operator()(const info &a, const info &b)
    {
        if (a.c != b.c)
            return a.c > b.c;
        return a.did < b.did;
    }
};

void read()
{
    cin >> n;
    
    for (int i = 1; i <= n; i++)
        cin >> clo[i];
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
}

int result[5005][2];
bool visited[5005][2];

int dijkstra()
{
    priority_queue<info, vector<info>, compare> pq;

    pq.push({1, 0, 0});

    while (!pq.empty())
    {
        auto acc = pq.top();
        pq.pop();

        if (visited[acc.v][acc.did])
            continue;
        visited[acc.v][acc.did] = true;
        result[acc.v][acc.did] = acc.c;

        if (!visited[acc.v][true])
            pq.push({acc.v, acc.c + clo[acc.v] / 2, true});

        for (auto i : g[acc.v])
            if (!visited[i.first][acc.did])
                pq.push({i.first, acc.c + i.second, acc.did});
    }
    
    return result[1][1];
}

int solve()
{
    return dijkstra();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << solve();
}