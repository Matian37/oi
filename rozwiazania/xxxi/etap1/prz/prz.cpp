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


// 1 -> n kolumny
// n + 1 -> 2n wiersze

const int maxn = 100000, maxm = 500000;

vector<ii> graph[maxn * 2 + 10];
ii buttons[maxm + 10];
int kol[maxn + 5], wier[maxn + 5], fu[maxn * 2 + 10], ranks[maxn * 2 + 10];
bool visited[maxn * 2 + 10], buttonStan[maxm + 10], possible = true;
int n, m;

void read()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> buttons[i].first >> buttons[i].second;
        buttonStan[i] = true;
        kol[buttons[i].second]++;
        wier[buttons[i].first]++;
    }
}

int find(int a)
{
    if (fu[a] == a)
        return a;
    return fu[a] = find(fu[a]);
}

bool Union(int a, int b)
{
    int fa = find(a), fb = find(b);

    if (fa == fb)
        return false;
    
    if (ranks[fa] < ranks[fb])
    {
        ranks[fb] += ranks[fa];
        fu[fa] = fb;
    }
    else
    {
        ranks[fa] += ranks[fb];
        fu[fb] = fa;
    }

    return true;
}

void initFu()
{
    for (int i = 1; i <= 2 * n; i++)
    {
        fu[i] = i;
        ranks[i] = 1;
    }
}

int DFS(int v, int p, int button, bool par)
{
    int sum = (v <= n ? kol[v] % 2 != par : wier[v - n] % 2 != par);

    visited[v] = true;

    for (auto i : graph[v])
    {
        if (i.first == p)
            continue;
        sum += DFS(i.first, v, i.second, par);
    }

    sum %= 2;

    if (sum == 1)
    {
        if (p == -1)
            possible = false;
        else
            buttonStan[button] = !buttonStan[button];
    }

    return sum;
}

void solve()
{
    initFu();

    for (int i = 0; i < m; i++)
    {
        if (Union(buttons[i].first + n, buttons[i].second))
        {
            graph[buttons[i].first + n].push_back({buttons[i].second, i});
            graph[buttons[i].second].push_back({buttons[i].first + n, i});
            //cout << buttons[i].first + n << ' ' << buttons[i].second << '\n';
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (kol[i] == 0 || wier[i] == 0)
        {
            possible = false;
            break;
        }
    }

    if (possible)
    {
        for (int i = 1; i <= 2 * n; i++)
        {
            if (!visited[i])
                DFS(i, -1, 0, true);
            if (!possible)
                break;
        }
    }


    if (!possible)
    {
        possible = true;

        for (int i = 0; i < m; i++)
            buttonStan[i] = true;
        for (int i = 1; i <= 2 * n; i++)
            visited[i] = false;
        for (int i = 1; i <= 2 * n; i++)
        {
            if (!visited[i])
                DFS(i, -1, 0, false);
            if (!possible)
                break;
        }

        int c = 0;
        for (int i = 0; i < m; i++) if (buttonStan[i]) c++;

        if (c == 0)
            possible = false;
    }

    if (possible)
    {
        cout << "TAK\n";

        int c = 0;

        for (int i = 0; i < m; i++) if (buttonStan[i]) c++;

        cout << c << '\n';

        for (int i = 0; i < m; i++) if (buttonStan[i]) cout << i + 1 << ' ';
    }
    else
        cout << "NIE";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}