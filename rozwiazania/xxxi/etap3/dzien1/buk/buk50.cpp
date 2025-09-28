#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, int> pli;

const int Z = 1e6 + 5, N = 20, NMAX = 1 << 20;

bitset<NMAX> visited;
ll a[N], b[N];
pair<ll, int> zaklad[Z];
ll dp[NMAX];
int n, z;

int convertToInt(string& s)
{
    int val = 0;

    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1')
            val += 1 << i;
    return val;
}

bool inline isOn(int val, int p)
{
    return (val & (1 << p)) != 0;
}

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    
    cin >> z;

    for (int i = 0; i < z; i++)
    {
        string s;
        ll val = 0;

        cin >> s >> val;

        val *= -1;

        int v = convertToInt(s);

        for (int j = 0; j < n; j++)
            if (s[j] == '0')
                val += a[j];
            else
                val += b[j];

        zaklad[i] = {val, v};
    }
}

void init()
{
    for (int i = 0; i < NMAX; i++)
        dp[i] = LLONG_MIN;
    for (int i = 0; i < z; i++)
        if (dp[zaklad[i].second] < zaklad[i].first)
            dp[zaklad[i].second] = zaklad[i].first;

    priority_queue<pair<ll, int>> q;

    for (int i = 0; i < z; i++)
        q.push(zaklad[i]);
    
    while (!q.empty())
    {
        auto acc = q.top().second;
        q.pop();

        if (visited[acc]) continue;

        visited[acc] = true;

        for (int i = 0; i < n; i++)
        {
            int nxt = acc ^ (1 << i);
            ll val = dp[acc] - (isOn(acc, i) ? b[i] : a[i]);

            if (dp[nxt] < val)
            {
                dp[nxt] = val;
                q.push({dp[nxt], nxt});
            }
        }
    }
}

void solveQueries()
{
    int zap;
    cin >> zap;

    while (zap--)
    {
        string s;
        cin >> s;

        int p = convertToInt(s);

        cout << dp[p] << ' ' << 1 << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    init();
    solveQueries();
}