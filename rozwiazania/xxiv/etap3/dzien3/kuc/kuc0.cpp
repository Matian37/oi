//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize ("Ofast")
#pragma GCC optimize("unroll-loops")

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'
#define min3(x, y, z) min(x, min(y, z))
#define max3(x, y, z) max(x, max(y, z))
#define all(x) x.begin(),x.end()

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

constexpr ll N = 5e2 + 5, MAX = 6e7 + 5, add = 3e7;
ll t[N], r[N*N], c[MAX];
ll n, m = 0, sum;

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> t[i];
}

void solve()
{
    ull res = 0;

    for (int i = 0; i < n; i++)
    {
        sum = 0;

        for (int j = i; j < n; j++)
        {
            sum += t[j];
            r[m++] = sum;
            c[sum + add]++;
        }
    }

    sum = 0;

    for (int i = 0; i < m; i++)
    {
        sum -= r[i];

        for (int j = i + 1; j < m; j++)
        {
            sum -= r[j];
            res += c[sum + add] - (sum == r[j]) - (sum == r[i]);
            sum += r[j];
        }

        sum += r[i];
    }

    cout << res / 3LL << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}