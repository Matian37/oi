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

struct ulamek
{
    int a, b;
};

vector<int> graph[500005];
int parent[500005], n, k;

void read()
{
    cin >> n >> k;

    for (int i = 2; i <= n; i++)
    {
        int a;
        cin >> a;
        parent[i] = a;
        graph[a].push_back(i);
    }
}

ulamek min(const ulamek a, const ulamek b)
{
    if ((ull)a.a * (ull)b.b < (ull)b.a * (ull)a.b)
        return a;
    return b;
}

ulamek max(const ulamek a, const ulamek b)
{
    if ((ull)a.a * (ull)b.b > (ull)b.a * (ull)a.b)
        return a;
    return b;
}

ulamek result[500005];
int sajz[500005];

int sajzDFS(int v)
{
    sajz[v] = 1;

    for (int i : graph[v])
        sajz[v] += sajzDFS(i);
    return sajz[v];
}

void solveDFS(int v, int p)
{
    result[v] = {1, 1000000000};

    for (int i : graph[v])
    {
        solveDFS(i, v);
        result[v] = max(result[v], result[i]);
    }

    if (result[v].a == 1 && result[v].b == 1000000000)
        result[v] = {1000000000, 1};

    if (sajz[v] <= k)
        result[v] = min(result[v], {sajz[v], sajz[p] - 1});
}

double solve()
{
    if (n <= k)
        return 0.0;

    sajzDFS(1);
    solveDFS(1, -1);

    return (double)result[1].a / (double)result[1].b;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << fixed << setprecision(10) << solve();
}