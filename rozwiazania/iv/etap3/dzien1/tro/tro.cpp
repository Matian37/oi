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

bool t[1005][1005];
int n, m;

void read()
{
	cin >> n >> m;

	while (m--)
	{
		int a, b;
		cin >> a >> b;
		t[a][b] = t[b][a] = true;
	}
}
 
int solve()
{
	if (n < 3) return 0;

	int r = (n * (n - 1) * (n - 2)) / 6,
		odj = 0;

	for (int i = 1; i <= n; i++)
	{
		int red = 0, black = -1;

		for (int j = 1; j <= n; j++)
			if (t[i][j]) red++;
			else black++;
		odj += red * black;
	}

	return r - (odj / 2);
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    read();
    cout << solve();
}
