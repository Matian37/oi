#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

using namespace std;

int p[500005], tabp[500005];

void initP(string &txt)
{
    int j = 0;

    for (int i = 2; i <= txt.size(); i++)
    {
        while (j > 0 && txt[j] != txt[i - 1])
            j = tabp[j];

        if (txt[j] == txt[i - 1]) j++;

        tabp[i] = j;
    }
}

void init(string &t, int w)
{
    int j = 0, m = w;

    p[0] = 0;
    p[1] = 0;

    for (int i = 2; i <= m; i++)
    {
        while (j > 0 && t[j] != t[i - 1])
            j = p[j];

        if (t[j] == t[i - 1])
            j++;

        p[i] = j;
    }
}

bool kmp(string &t, int w)
{
    init(t, w);

    int sofar = 0;

    int n = t.size(), m = w;

    int j = 0;

    for (int i = 1; i <= n; i++)
    {
        while (j > 0 && t[j] != t[i - 1])
            j = p[j];

        if (t[j] == t[i - 1])
            j++;

        if (j == m)
        {
            if (sofar + 1 >= i - m + 1)
                sofar = i;
            else return false;
            j = p[j];
        }
    }

    if (sofar + 1 < n) return false;
    return true;
}

int kan[1000005], l = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    string txt;

    cin >> txt;

    initP(txt);

    int pref = tabp[txt.size()];

    kan[l++] = pref;

    while (pref > 0 && tabp[pref] > 0)
    {
        kan[l++] = tabp[pref];
        pref = tabp[pref];
    }

    int limit = 0, minn = txt.size();

    for (int x = l - 1; x >= 0; x--)
    {
        auto i = kan[x];

        if (limit >= i) continue;

        if (!kmp(txt, i))
        {
            limit = i * 2;
        }
        else
        {
            minn = i;
            break;
        }
    }

    cout << minn;
}