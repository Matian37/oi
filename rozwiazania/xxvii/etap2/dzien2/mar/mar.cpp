//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
 
#define MOD1 1000000007ULL
#define MOD2 1000000009ULL
#define MOD3 1000000021ULL
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

const ull p1 = 13, p2 = 7, p3 = 11;

struct HASH
{
    ull h1, h2, h3;

    void operator+=(HASH a)
    {
        h1 = (h1 + a.h1) % MOD1;
        h2 = (h2 + a.h2) % MOD2;
        h3 = (h3 + a.h3) % MOD3;
    }

    bool operator==(HASH a) const
    {
        if (h1 != a.h1) return false;
        if (h2 != a.h2) return false;
        if (h3 != a.h3) return false;
        return true;
    }

    void operator-=(HASH a)
    {
        h1 = ((ll)h1 - (ll)a.h1 + (ll)MOD1) % (ll)MOD1;
        h2 = ((ll)h2 - (ll)a.h2 + (ll)MOD2) % (ll)MOD2;
        h3 = ((ll)h3 - (ll)a.h3 + (ll)MOD3) % (ll)MOD3;
    }
};

struct Hash
{
    size_t operator()(const HASH& a) const
    {
        return a.h1 ^ a.h2 ^ a.h3;
    }
};

unordered_map<HASH, int, Hash> h[18];
HASH t[18][100005], power[20];
string s;
int n, m;

void init()
{
    power[0] = {1, 1, 1};
    for (int i = 1; i < 20; i++)
    {
        power[i].h1 = (power[i - 1].h1 * p1) % MOD1;
        power[i].h2 = (power[i - 1].h2 * p2) % MOD2;
        power[i].h3 = (power[i - 1].h3 * p3) % MOD3;
    }

    for (int i = 0; i < n; i++)
    {
        t[1][i] = {s[i] - '0' + 1ULL, s[i] - '0' + 1ULL, s[i] - '0' + 1ULL};
        h[1][t[1][i]]++;
    }
    
    for (int i = 2; i <= log2(n); i++)
    {
        for (int j = 0; j < n - i + 1; j++)
        {
            t[i][j].h1 = (t[i - 1][j].h1 * p1 + (ull)(t[1][j + i - 1].h1 - '0' + 1)) % MOD1;
            t[i][j].h2 = (t[i - 1][j].h2 * p2 + (ull)(t[1][j + i - 1].h2 - '0' + 1)) % MOD2;
            t[i][j].h3 = (t[i - 1][j].h3 * p3 + (ull)(t[1][j + i - 1].h3 - '0' + 1)) % MOD3;
            h[i][t[i][j]]++;
        }
    }
}

void read()
{
    cin >> n >> m >> s;
}

int solveQuery()
{
    for (int i = 1; i <= log2(n); i++)
        if (h[i].size() < (1 << i))
            return i;
    return (int)log2(n) + 1;
}

void update(int pos)
{
    pos--;
    bool bit = (s[pos] - '0');
    bit = !bit;
    s[pos] = char((int)bit + '0');

    for (int i = 1; i <= log2(n); i++)
    {
        for (int j = max(0, pos - i + 1); j <= min(n - i, pos); j++)
        {
            HASH updated = t[i][j];
            int pot = j + i - pos - 1;

            if (!bit) updated -= power[pot];
            else updated += power[pot];

            auto v = h[i].find(t[i][j]);
            v->second--;
            if (v->second == 0) h[i].erase(v);

            h[i][updated]++;
            t[i][j] = updated;
        }
    }
}

void solve()
{
    init();

    cout << solveQuery() << '\n';

    while (m--)
    {
        int pos;
        cin >> pos;

        update(pos);

        cout << solveQuery() << '\n';
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    read();
    solve();
}