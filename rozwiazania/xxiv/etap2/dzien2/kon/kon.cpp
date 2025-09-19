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

struct info
{
    int a, l, d;
};

bool comp(const info &a, const info &b)
{
    if (a.d != b.d)
        return a.d < b.d;
    if ((a.a % a.d) != (b.a % b.d))
        return (a.a % a.d) < (b.a % b.d);
    return a.a < b.a;
}

vector<info> heavy;

const int m = 100005;

int sol[m], ad[m], rem[m];
int n, k;

void solve()
{
    cin >> n >> k;

    while (k--)
    {
        info a;
        cin >> a.a >> a.l >> a.d;

        if (a.l > sqrt(n))
            heavy.push_back(a);
        else
        {
            for (int i = a.a, l = 0; l < a.l; l++, i += a.d)
                sol[i]++;
        }
    }

    sort(heavy.begin(), heavy.end(), comp);

    for (int i = 0; i < heavy.size(); i++)
    {
        int add = 0, start = heavy[i].a, where = heavy[i].a + (heavy[i].l - 1) * heavy[i].d;

        ad[heavy[i].a]++;
        rem[heavy[i].a + (heavy[i].l - 1) * heavy[i].d]--;     

        while (i + 1 < heavy.size())
        {
            if ((heavy[i].a % heavy[i].d) != (heavy[i + 1].a % heavy[i + 1].d) || heavy[i].d != heavy[i + 1].d)
                break;
            i++;
            ad[heavy[i].a]++;
            rem[heavy[i].a + (heavy[i].l - 1) * heavy[i].d]--;
            where = max(where, heavy[i].a + (heavy[i].l - 1) * heavy[i].d );
            start = min(start, heavy[i].a);
        }

        for (int pos = start; pos <= where; pos += heavy[i].d)
        {
            add += ad[pos];
            sol[pos] += add;
            add += rem[pos];
            ad[pos] = rem[pos] = 0;
        }
        
    }

    for (int i = 1; i <= n; i++)
        cout << sol[i] << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    solve();
}