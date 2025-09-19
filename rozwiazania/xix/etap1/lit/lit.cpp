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

int n;
string a, b;

const int base = 1 << 20;

int tree[base * 2];
list<int> wstp[26];

void update(int a, int b, int v)
{
    a += base - 1;
    b += base + 1;

    while (a / 2 != b / 2)
    {
        if (a % 2 == 0)
            tree[a + 1] += v;
        if (b % 2 == 1)
            tree[b - 1] += v;
        a /= 2;
        b /= 2;
    }
}

int query(int a)
{
    a += base;

    int r = 0;

    while (a != 0)
    {
        r += tree[a];
        a /= 2;
    }
    
    return r;
}

void read()
{
    cin >> n >> a >> b;
}

ll solve()
{
    for (int i = 0; i < n; i++)
    {
        update(i, i, i);
        wstp[b[i] - 65].push_back(i);
    }
    
    ll r = 0;

    for (int i = 0; i < n; i++)
    {
        int pos = wstp[a[i] - 65].front();
        wstp[a[i] - 65].pop_front();

        r += (ll)query(pos);
        update(pos + 1, n, -1);
    }

    return r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << solve();
}