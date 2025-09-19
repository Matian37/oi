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
    int first, second, val;
};

info p[10005];
int pref[605];
ii hull[605];

int dp[605][605];
int rem[605][605];

int n, m, punkt, sc = 0;

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> hull[i].first >> hull[i].second;
    }

    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> p[i].first >> p[i].second >> p[i].val;
        sc += p[i].val;
    }
}

int cross(const ii& a, const ii& b, const ii& c)
{
    return (a.first - c.first) * (b.second - c.second) -
           (a.second - c.second) * (b.first - c.first);
}

bool comp(const info& a, const info& b)
{
    return cross({b.first, b.second}, {a.first, a.second}, hull[punkt]) > 0;
}

void init()
{
    for (int i = 0; i < n; i++)
    {
        punkt = i;
        sort(p, p + m, comp);

        int k = 0;

        for (int j = (i + 2) % n; j != i; j = (j + 1) % n)
        {
            int pop = (j - 1 + n) % n;

            dp[i][j] += dp[i][pop];

            while (k < m)
            {
                if (cross(hull[pop], {p[k].first, p[k].second}, hull[i]) != 0)
                    break;
                if (hull[i].first == p[k].first && hull[i].second == p[k].second)
                    {k++; continue;}
                dp[i][j] += p[k++].val;
            }
            while (k < m)
            {
                if (cross(hull[j], {p[k].first, p[k].second}, hull[i]) <= 0)
                    break;
                if (hull[i].first == p[k].first && hull[i].second == p[k].second)
                    {k++; continue;}
                dp[i][j] += p[k++].val;
            }
        }
    }
}

int getTriangle(int a, int b, int c)
{
    int r = sc;

    if (cross(hull[c], hull[b], hull[a]) > 0) r -= dp[a][b];
    else r -= dp[b][a];
    if (cross(hull[a], hull[c], hull[b]) > 0) r -= dp[b][c];
    else r -= dp[c][b];
    if (cross(hull[b], hull[c], hull[a]) > 0) r -= dp[a][c];
    else r -= dp[c][a];

    return r;
}

void solve()
{
    init();

    int r = INT32_MIN;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                r = max(r, getTriangle(i, j, k));
    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}