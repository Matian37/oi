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

vector<int> graph[505];
vector<int> general;
bool visited[505];
int wsk[505];
int n;

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m;

        if (m == 0)
            general.push_back(i + 1);

        for (int j = 0; j < m; j++)
        {
            int a;
            cin >> a;
            graph[a].push_back(i + 1);
        }
    }
}

void solve()
{
    queue<int> confirmed;

    for (int i : general)
    {
        visited[i] = true;

        for (int j : graph[i])
            wsk[j]++;
    }


    for (int i = 1; i <= n; i++)
        if (wsk[i] > 1)
            confirmed.push(i);

    while (!confirmed.empty())
    {
        auto acc = confirmed.front();
        confirmed.pop();

        visited[acc] = true;

        for (int i : graph[acc])
            if (!visited[i])
                confirmed.push(i);
    }

    bool did = false;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            cout << i << '\n';
            did = true;
        }
    }

    if (!did)
        cout << "BRAK\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}