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
    int x, y, id;
};

bool compY(const info& a, const info& b)
{
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
};

bool compX(const info& a, const info& b)
{
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
};

set<info, decltype(*compY)> kop(compY), dys(compY);
set<info, decltype(*compX)> acc(compX);
int n;

void read()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        ii a;
        cin >> a.first >> a.second;

        kop.insert({a.first, a.second, i});
    }

    for (int i = 1; i <= n; i++)
    {
        ii a;
        cin >> a.first >> a.second;

        dys.insert({a.first, a.second, i});
    }
}

void update(set<info, decltype(&compX)>::iterator &it, int y)
{
    while (it != dys.end())
    {
        if (it->y > y) break;
        acc.insert(*it);
        it++;
    }
}

ull getDist(info a, info b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void solve()
{
    ull dist = 0;

    vector<ii> result;

    auto it = dys.begin();

    for (auto i : kop)
    {
        update(it, i.y);

        auto f = acc.lower_bound({i.x, 0, 0});

        dist += getDist(i, *f);
        result.push_back({i.id, f->id});

        acc.erase(f);
    }

    cout << dist << '\n';

    for (auto i : result)
        cout << i.first << ' ' << i.second << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}