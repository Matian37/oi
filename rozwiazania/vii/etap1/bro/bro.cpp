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
#define left first
#define right second

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

ull res = ULLONG_MAX;
int pref[10005], zap[10005], nastp[10005];
int n;

void read()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> zap[i - 1] >> nastp[i - 1];
        pref[i] = pref[i - 1] + nastp[i - 1];
    }
}

int getOdl(int v, int w)
{
    if (v <= w) return pref[w] - pref[v];
    else return pref[n] - pref[v] + pref[w];
}

int getMod(int v)
{
    if (v == n) return 0;
    if (v == -1) return n - 1;
    return v;
}

void solve()
{
    int l = 0, r = 0;
    pull sumZap = {0,0};
    ull vL = 0, vR = 0;

    while (getMod(r + 1) != 0)
    {
        if (getOdl(0, getMod(r + 1)) >= getOdl(getMod(r + 1), 0)) break;

        r = getMod(r + 1);
        sumZap.right += (ull)zap[r];
        vR += (ull)getOdl(0, r) * (ull)zap[r];
    }

    while (getMod(l - 1) != r)
    {
        l = getMod(l - 1);
        sumZap.left += (ull)zap[l];
        vL += (ull)getOdl(l, 0) * (ull)zap[l];
    }

    for (int i = 0; i < n; i++)
    {
        res = min(res, vL + vR);

        if (i == n - 1) continue;

        if (i == r)
        {
            vL -= (ull)getOdl(i + 1, i) * (ull)zap[i + 1];
            sumZap.left += (ull)zap[i];
            sumZap.left -= (ull)zap[i + 1];
            vL += (ull)getOdl(i, i + 1) * (ull)sumZap.left;
            r = getMod(r + 1);
            l = getMod(l + 1);
        }
        else
        {
            vR -= (ull)getOdl(i, i + 1) * (ull)sumZap.right;
            sumZap.left += (ull)zap[i];
            sumZap.right -= (ull)zap[i + 1];
            vL += (ull)getOdl(i, i + 1) * (ull)sumZap.left;
        }

        while (getMod(r + 1) != i + 1)
        {
            if (getOdl(i + 1, getMod(r + 1)) >= getOdl(getMod(r + 1), i + 1))
                break;

            r = getMod(r + 1);
            l = getMod(l + 1);

            vL -= (ull)getOdl(r, i + 1) * (ull)zap[r];
            sumZap.left -= (ull)zap[r];
            sumZap.right += (ull)zap[r];
            vR += (ull)getOdl(i + 1, r) * (ull)zap[r];
        }
        while (getOdl(i + 1, r) > getOdl(r, i + 1))
        {
            vR -= (ull)getOdl(i + 1, r) * (ull)zap[r];
            sumZap.right -= (ull)zap[r];
            sumZap.left += (ull)zap[r];
            vL += (ull)getOdl(r, i + 1) * (ull)zap[r];

            r = getMod(r - 1);
            l = getMod(l - 1);
        }
    }

    cout << res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}