//
// Mateusz Pietrowcow
//
// howDoesInputLikeThis???
// howDoesInputLikeThis???
// howDoesInputLikeThis???
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

const int N = 4'000'010;

int str[N], corr[N], t[N];
ii fuckinInput[N];
int n, m, k, incrr;
bool oszust;

void read()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> fuckinInput[i].first;
        k += fuckinInput[i].first;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> fuckinInput[i].second;
        corr[fuckinInput[i].second] = fuckinInput[i].first;
    }
    for (int i = 0; i < n; i++)
        cin >> str[i];
}

int changed(int a, int v)
{
    if (t[a] + v == corr[a])
        return -1;
    if (t[a] == corr[a])
        return 1;
    return 0;
}

int solve()
{
    if (k <= 0) return 0;
    if (k > n) return 0;

    for (int i = 0; i < k; i++)
        t[str[i]]++;

    for (int i = 1; i < N; i++)
        if (t[i] != corr[i])
            incrr++;

    int c = 0;

    for (int i = k - 1; i < n; i++)
    {
        if (incrr == 0) c++;

        incrr += changed(str[i - k + 1], -1);
        t[str[i - k + 1]]--;

        incrr += changed(str[i + 1], 1);
        t[str[i + 1]]++;
    }

    return c;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << solve();
}