//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

struct info
{
    ii first;
    int second;
    bool ends;
};

vector<info> p;
ii indeks[1000005];
int goBack[1000005], ile[1000005], dp[1000005][2];
bool visited[1000005];
int n, k;


ll cross0(pll a, pll b)
{
    return a.first * b.second - a.second * b.first;
}

void read()
{
    cin >> k >> n;

    for (int i = 1; i <= n; i++)
    {
        ii a, b;
        cin >> a.first >> a.second >> b.first >> b.second;

        if (cross0(a, b) == 0)
        {
            if (a.first > b.first) swap(a, b);
            else if (a.second > b.second) swap(a, b);
        }
        else if (cross0(a, b) < 0) swap(a, b);

        p.push_back({a, i, false});
        p.push_back({b, i, true});
    }
}

bool comp(const info& a, const info& b)
{
    if (cross0(a.first, b.first) == 0)
    {
        if (a.ends != b.ends) return a.ends < b.ends;
        if (a.first.first != b.first.first) return a.first.first < b.first.first;
        return a.first.second < b.first.second;
    }
    return cross0(a.first, b.first) > 0;
}

void solve()
{
    sort(p.begin(), p.end(), comp);

    p.push_back({{-2, 2}, 0, false});

    multiset<int> s;

    int c = 0, len = 1;

    for (int i = 0; i < p.size() - 1; i++)
    {
        auto acc = p[i];

        if (!p[i].ends)
        {
            indeks[p[i].second].first = len;
            s.insert(indeks[p[i].second].first);
            c++;

            if (cross0(p[i].first, p[i + 1].first) != 0 || p[i + 1].ends)
            {
                ile[len] = c;

                if (s.size() == 0) goBack[len] = 0;
                else goBack[len] = (*s.begin()) - 1;
                len++;
            }
        }
        else
        {
            s.erase(s.lower_bound(indeks[p[i].second].first));
            c--;

            if (cross0(p[i].first, p[i + 1].first) != 0)
            {
                ile[len] = c;

                if (s.size() == 0) goBack[len] = 0;
                else goBack[len] = (*s.begin()) - 1;
                len++;
            }
        }
    }

    int maks = 0;

    for (int j = 1; j <= k; j++)
    {
        for (int i = 1; i < len; i++)
        {
            dp[i][j % 2] = max(dp[i - 1][j % 2], dp[goBack[i]][(j - 1) % 2] + ile[i]);
        }
        maks = max(maks, dp[len - 1][j % 2]);
    }

    cout << maks;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}