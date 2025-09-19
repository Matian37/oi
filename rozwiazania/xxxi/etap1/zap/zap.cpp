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

struct info
{
    int a, b, id;
};

info t[500005];
vector<ii> solution1, solution2;
int n;

bool comp(const info& a, const info& b)
{
    if (a.b != b.b) return a.b < b.b;
    return a.a > b.a;
}

bool comp2(const info& a, const info& b)
{
    if (a.b != b.b) return a.b < b.b;
    return a.a < b.a;
}

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> t[i].a >> t[i].b;
        t[i].id = i;
    }
}

void solve1()
{
    sort(t, t + n, comp2);

    vector<int> elements;
    int sofar = -1;

    for (int i = 0; i < n; i++)
    {
        if (t[i].a < sofar)
            continue;
        sofar = t[i].b;
        elements.push_back(i);
    }

    for (int i = 0; i < (int)elements.size() - 1; i++)
        solution1.push_back({t[elements[i]].id, t[elements.back()].id});

}

void solve2()
{
    sort(t, t + n, comp);

    int last = 0;
    int sofarF = -1, sofarS = -1;

    for (int i = 1; i < n; i++)
    {
        if (t[i].a < sofarF) continue;
        if (last == -1) last = i;
        else if (t[i].a < sofarS)
        {
            if (t[last].a < sofarS) continue;

            solution2.push_back({t[last].id, t[i].id});
            sofarF = t[last].b;
            sofarS = t[i].b;
            last = -1;
        }
        else if (t[last].a >= sofarS)
        {
            solution2.push_back({t[last].id, t[i].id});
            sofarF = t[last].b;
            sofarS = t[i].b;
            last = -1;         
        }
        else
        {
            solution2.push_back({t[i].id, t[last].id});
            sofarF = t[i].b;
            sofarS = t[i].b;
            last = -1;
        }
    }
}

void solve()
{
    solve1();
    solve2();

    if (solution1.size() < solution2.size())
    {
        cout << solution2.size() << '\n';

        for (auto i : solution2)
           cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }
    else
    {
        cout << solution1.size() << '\n';

        for (auto i : solution1)
            cout << i.first + 1 << ' ' << i.second + 1 << '\n';
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