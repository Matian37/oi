//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000
#define ii pair<int,int>
#define pll pair<long long, long long>
#define pul pair<unsigned long long, unsigned long long>
#define Tak cout << "TAK" << '\n';
#define Nie cout << "NIE" << '\n';

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

using namespace std;

struct info
{
    ull n, zwieksz, czas;
};

struct compare
{
    bool operator()(const info &a, const info &b)
    {
        if (a.czas != b.czas)
            return a.czas > b.czas;
        if (a.n != b.n)
            return a.n < b.n;
        return a.zwieksz < b.zwieksz;
    }
};

map<pair<ull, ull>, bool> visited;

ull branchAndBound(ull a, ull b, ull n)
{
    priority_queue<info, vector<info>, compare> pq;

    pq.push({1, 1, a}); 

    while (!pq.empty())
    {
        auto acc = pq.top();
        pq.pop();

        if (acc.n > n)
            return acc.czas;
        if (visited[{acc.n, acc.zwieksz}])
            continue;
        visited[{acc.n, acc.zwieksz}] = true;


        pq.push({acc.n + acc.zwieksz, acc.zwieksz, acc.czas + b}); 
        pq.push({acc.n, acc.n, acc.czas + a}); 
    }

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    ull n, a, b;
    cin >> n >> a >> b;

    cout << branchAndBound(a, b, n) << '\n';
}