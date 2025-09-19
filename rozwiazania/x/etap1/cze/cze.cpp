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

int vx[1005], vy[1005];
int prefX[1005], prefY[1005];
int n, m, sum = 0;

void read()
{
    cin >> n >> m;
    n--; m--;

    for (int i = 1; i <= n; i++)
        cin >> vx[i];

    for (int i = 1; i <= m; i++)
    {
        cin >> vy[i];
        prefY[i] = prefY[i - 1] + vy[i];
    }
}

int getResult(int pos, int value)
{
    return (pos + 1) * value + sum + prefX[n] - prefX[pos];
}

int getPos(int pos, int value)
{
    return (pos + 1) * value + prefX[n] - prefX[pos];
}

int solve()
{
    sort(vx + 1, vx + (n + 1), greater<int>());

    for (int i = 1; i <= n; i++)
        prefX[i] = prefX[i - 1] + vx[i];

    sum = prefX[n];

    for (int i = 1; i <= m; i++)
    {
        int bestValue = getResult(0, vy[i]), best = 0;

        for (int j = 1; j <= n; j++)
        {
            if (bestValue >= getResult(j, vy[i]))
            {
                bestValue = getResult(j, vy[i]);
                best = j;
            }
        }

        sum += getPos(best, vy[i]);
    }

    return sum;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << solve();
}