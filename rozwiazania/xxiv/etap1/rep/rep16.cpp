//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000
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

int t[] = {1, 2, 4, 8, 16, 21, 42, 51, 102, 112, 224, 235, 470, 486, 972, 990, 1980, 2002, 4004, 4027, 8054, 8078, 16156, 16181, 32362, 32389, 64778, 64806, 129612, 129641, 259282, 259313, 518626, 518658, 1037316, 1037349, 2074698, 
2074734, 4149468, 4149505, 8299010, 8299049, 16598098, 16598140, 33196280, 33196324, 66392648, 66392693, 132785386, 132785432, 265570864, 265570912, 531141824, 531141876};

int n;

void solve(int v)
{
    const int sajz = sizeof(t) / sizeof(int);

    if ( v == 0)
    {
        cout << "1 1\n";
        return;
    }

    for (int i = 0; i < sajz; i++)
    {
        for (int j = i + 1; j < sajz; j++)
        {
            if (t[j] - t[i] == v)
            {
                cout << j + 1 << ' ' << i + 1 << '\n';
                return;
            }  
        }
    }


}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    cin >> n;

    while (n--)
    {
        int a;
        cin >> a;
        solve(a);      
    }
    


}