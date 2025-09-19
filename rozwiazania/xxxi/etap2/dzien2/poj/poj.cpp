#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef pair<int,int> ii;
typedef long long ll;
typedef unsigned long long ull;

struct anws
{
    ll m;
    int a;
    ll b;
    int c;
    ll d;
};

pair<ll,int> t[1000005], val;
anws v[1000005];
ll k, sum = 0, wsk = 0, sumUsed = 0;
int n;

void read()
{
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> t[i].first;
        sum += t[i].first;
        t[i].second = i;
    }
}

void addAnws(int pos)
{
    v[pos].m++;

    if (v[pos].m == 1)
    {
        v[pos].a = val.second;
        v[pos].b = val.first;
    }
    else
    {
        v[pos].c = val.second;
        v[pos].d = val.first;
    }
}

struct compare
{
    bool operator()(const pair<ll, int>& a, const pair<ll, int>& b) const
    {
        if (v[a.second].m != v[b.second].m) return v[a.second].m < v[b.second].m;
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    }
};

void solve()
{
    if ((ll)n * k < sum)
    {
        cout << "NIE";
        return;
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, compare> pozycja;
    set<pair<ll, int>> pq;

    for (int i = 1; i <= n; i++)
    {
        pq.insert(t[i]);
        pozycja.push({k, i});
    }

    while (!pq.empty())
    {
        auto place = pozycja.top();
        pozycja.pop();

        if (v[place.second].m == 0)
        {
            auto acc = *pq.begin();
            pq.erase(pq.begin());

            if (place.first >= acc.first)
            {
                val = acc;
                addAnws(place.second);
                
                if (place.first != acc.first)
                    pozycja.push({place.first - acc.first, place.second});
            }
            else
            {
                val = {place.first, acc.second};
                addAnws(place.second);
                pq.insert({acc.first - place.first, acc.second});
            }
        }
        else
        {
            auto it = pq.lower_bound({place.first, 0});

            if (it == pq.end()) 
            {
                it = pq.end();
                it--;
            }
            auto acc = *it;
            pq.erase(it);

            if (place.first >= acc.first)
            {
                val = acc;
                addAnws(place.second);
            }
            else if (place.first < acc.first)
            {
                val = {place.first, acc.second};
                addAnws(place.second);
                pq.insert({acc.first - place.first, acc.second});
            }
            
        }
    }

    cout << "TAK\n";

    for (int i = 1; i <= n; i++)
    {
        if (v[i].m == 0) cout << "0\n";
        else if (v[i].m == 1)
        {
            cout << 1 << ' ' << v[i].a << ' ' << v[i].b << '\n';
        }
        else
        {
            cout << 2 << ' ' << v[i].a << ' ' << v[i].b << ' ' << v[i].c << ' ' << v[i].d << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    read();
    solve();
}