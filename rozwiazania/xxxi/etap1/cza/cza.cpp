//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define MOD1 1000000007LL
#define MOD2 1000000009LL
#define MOD3 1000000021LL
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'
#define min3(x, y, z) min(x, min(y, z))
#define max3(x, y, z) max(x, max(y, z))

#define h1 first.first
#define h2 first.second
#define h3 second

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;
typedef pair<ii,int> HASH;

const ll prime = 37;
int id = -1;

struct Hash
{
    size_t operator()(const HASH& a) const
    {
        return (hash<int>()(a.h1)) ^ (hash<int>()(a.h2)) ^ (hash<int>()(a.h3));
    }
};

gp_hash_table<HASH, int, Hash> hID, wstp;
vector<vector<int>> letters;
vector<HASH> h, pot;
string s;
int n, oldn, k;
ull pocz, kon;

void read()
{
    cin >> n >> k >> pocz >> kon;
    cin >> s;
    s = '_' + s;
}

void update(int i)
{
    auto acc = h.back();

    h.push_back({{},{}});

    h.back().h1 = ((ll)acc.h1 * prime + (ll)(s[i] - 'a' + 1)) % MOD1;
    h.back().h2 = ((ll)acc.h2 * prime + (ll)(s[i] - 'a' + 1)) % MOD2;
    h.back().h3 = ((ll)acc.h3 * prime + (ll)(s[i] - 'a' + 1)) % MOD3;
}

HASH query(int a, int b)
{
    HASH acc = h[b];

    acc.h1 = ((((ll)acc.h1 - ((ll)h[a - 1].h1 * (ll)pot[b - a + 1].h1)) % MOD1) + MOD1) % MOD1;
    acc.h2 = ((((ll)acc.h2 - ((ll)h[a - 1].h2 * (ll)pot[b - a + 1].h2)) % MOD2) + MOD2) % MOD2;
    acc.h3 = ((((ll)acc.h3 - ((ll)h[a - 1].h3 * (ll)pot[b - a + 1].h3)) % MOD3) + MOD3) % MOD3;

    return acc;
}

int addNew()
{
    id++;
    letters.push_back({});

    for (int i = 0; i < 26; i++)
        letters[id].push_back(0);
    return id;
}

void init()
{
    h.push_back({{0, 0}, 0});
    pot.push_back({{1, 1}, 1});

    for (int i = 1; i <= n; i++)
        update(i);
    for (int i = 1; i <= k; i++)
    {
        auto acc = pot.back();

        pot.push_back({{},{}});
        pot.back().h1 = ((ll)acc.h1 * prime) % MOD1;
        pot.back().h2 = ((ll)acc.h2 * prime) % MOD2;
        pot.back().h3 = ((ll)acc.h3 * prime) % MOD3;
    }
    
    for (int i = 1; i <= n - k; i++)
    {
        auto v = query(i, i + k - 1);
        auto acc = hID.find(v);

        if (acc == hID.end())
        {
            hID[v] = addNew();
            letters[id][s[i + k] - 'a']++;
        }
        else
            letters[acc->second][s[i + k] - 'a']++;
    }
}

void solve()
{
    wstp.clear();
    hID.clear();

    oldn = n;
    init();

    HASH acc = query(n - k + 1, n);
    auto check = wstp.find(acc);

    while (check == wstp.end())
    {
        auto pos = hID.find(acc);

        int best = 0;
        char znak = 'a';

        if (pos != hID.end())
        {
            for (int i = 0; i < 26; i++)
            {
                if (best < letters[pos->second][i])
                {
                    best = letters[pos->second][i];
                    znak = char(int('a') + i);
                }
            }
        }
        else
        {
            hID[acc] = addNew();
            pos = hID.find(acc);
        }

        wstp[acc] = n + 1;
        s.push_back(znak);
        update(++n);
        letters[pos->second][s[n] - 'a']++;
        acc = query(n - k + 1, n);
        check = wstp.find(acc);
    }

    int cyklP = check->second, cyklK = n;

    if (kon <= cyklP)
    {
        for (int i = pocz; i <= kon; i++)
            cout << s[i];
    }
    else if (pocz <= cyklP)
    {
        for (pocz; pocz < cyklP; pocz++)
            cout << s[pocz];
        
        int j = 0;

        while (pocz <= kon)
        {
            cout << s[cyklP + j];
            j = (j + 1) % (cyklK - cyklP + 1);
            pocz++;
        }
    }
    else
    {
        pocz -= cyklP - 1;
        kon -= cyklP - 1;

        int j = (pocz - 1) % (cyklK - cyklP + 1), czas = kon - pocz + 1;

        while (czas--)
        {
            cout << s[cyklP + j];
            j = (j + 1) % (cyklK - cyklP + 1);
        }
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