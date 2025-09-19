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
    int a, b, id;
};

bool compP(const info &a, const info &b)
{
    return a.a < b.a;
}

bool compK(const info &a, const info &b)
{
    return a.b < b.b;
}

info pp[1000005], pk[1000005], p[1000005];
int n, k;

void read()
{
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> pp[i].a >> pp[i].b;
        pp[i].id = i;
        pk[i] = pp[i];
        p[i] = pk[i];
    }
}

multiset<int> ranges;

int a, b, c;

void getAnws()
{
    cout << c << '\n';

    int r = 0;

    for (int i = 0; i < n; i++)
    {
        if (a < p[i].a || p[i].b < b)
            continue;
        cout << p[i].id + 1 << ' ';
        r++;
        if (r == k)
            break;
    }
}

void solve()
{
    sort(pp, pp + n, compP);
    sort(pk, pk + n, compK);

    int i = 0, j = 0;

    while (i < n)
    {
        if (pp[i].b >= pk[j].b)
            ranges.insert(pp[i].b);
        
        if (pk[j].b - pp[i].a > c && ranges.size() >= k)
        {
            c = pk[j].b - pp[i].a;
            b = pk[j].b;
            a = pk[i].a;
        }

        while (j != n - 1 && ranges.size() >= k)
        {
            auto en = ranges.lower_bound(pk[j + 1].b);

            if (ranges.size() - distance(ranges.begin(), en) < k)
                break;
            j++;
            
            stack<int> rem;

            for (auto it = ranges.begin(); it != en; it++)
                rem.push(*it);
            while (!rem.empty())
            {
                ranges.erase(rem.top());
                rem.pop();
            }
            
            if (pk[j].b - pp[i].a > c)
            {
                c = pk[j].b - pp[i].a;
                b = pk[j].b;
            }
        }

        i++;

        while(pp[i].a > pk[j].b)
        {
            j++;
            auto en = ranges.lower_bound(pk[j].b);

            stack<int> rem;

            for (auto it = ranges.begin(); it != en; it++)
                rem.push(*it);
            while (!rem.empty())
            {
                ranges.erase(rem.top());
                rem.pop();
            }
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
    getAnws();
}