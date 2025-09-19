#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

typedef pair<int,int> ii;
typedef long long ll;
typedef unsigned long long ull;

const int N = 300005;

ull cost[N], stan[N];
ull r = 0;
int can[N], n, m;

void read()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    
    for (int i = 1; i <= n; i++)
        cin >> stan[i];
}

int day[N];

int best(int a, int b)
{
    return (cost[a] > cost[b] ? a : b);
}

void wrzuc(vector<ii>& a, set<ii, greater<ii>> &b, int K)
{
    while (a.size() != 0)
    {
        if (a.back().first > K) break;
        b.insert({cost[a.back().second], a.back().second});
        a.pop_back();
    }
}

bool comp(const ii& a, const ii& b)
{
    return a.first > b.first;
}

bool solveQuery()
{
    for (int i = 1; i <= n; i++)
    {
        cin >> day[i];
    }

    sort(day + 1, day + (n + 1));

    vector<ii> v;

    for (int i = 1; i <= n; i++)
    {
        int low = 1, high = n, med;

        while (low != high)
        {
            med = (low + high) / 2;

            if (stan[i] > day[med]) 
                low = med + 1;
            else
                high = med;
        }

        if (stan[i] > day[low]) 
            return false;

        can[i] = low;
        v.push_back({low, i});
    }

    sort(v.begin(), v.end(), comp);

    set<ii, greater<ii>> s;
    int c = 0, k = 1;

    while (k <= n)
    {
        wrzuc(v, s, k);

        if (s.size() != 0)
        {
            auto acc = *s.begin();
            s.erase(s.begin());
            r += (ull)(day[k] - stan[acc.second]) * (ull)acc.first;
            stan[acc.second] = day[k];
            c++;
        }

        k++;
    }

    return c == n;
}

void solve()
{
    cost[0] = 0;

    for (int i = 0; i < m; i++)
        if (!solveQuery())
        {
            cout << "NIE";
            return;
        }

    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    read();
    solve();
}