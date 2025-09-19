//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "arc.h"

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<uint,uint> uii;
typedef pair<ll,ll> pll;
typedef pair<ull,ull> pull;

#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())

const int K = 1e6 + 5;

struct listNode
{
    int val;
    listNode *prv, *nxt;
};

struct flist
{
    listNode *begin, *end;
    int size = 0;

    void add(int _val)
    {
        listNode* ptr = new listNode;

        size++;

        if (end == NULL)
        {
            begin = end = ptr;
            ptr->val = _val;
            ptr->prv = ptr->nxt = NULL;
        }
        else
        {
            ptr->val = _val;
            end->nxt = ptr;
            ptr->prv = end;
            ptr->nxt = NULL;
            end = ptr;
        }
    }

    inline void cutOff(listNode* a)
    {
        if (a == begin) begin = a->nxt;

        if (a->prv != NULL)
            a->prv->nxt = a->nxt;
        a->nxt->prv = a->prv;
    }

    void remadd(listNode* a, int _val)
    {
        cutOff(a);

        end->nxt = a;
        a->prv = end;
        a->nxt = NULL;
        a->val = _val;
        end = a;
    }

    void print()
    {   
        listNode* a = begin;

        while (a != NULL)
        {
            wypisz(a->val);
            a = a->nxt;
        }
    }
};

namespace sol
{
    flist t;

    int k;

    void readK()
    {
        while (t.size != k)
        {
            int in = wczytaj();
            t.add(in);
        }
    }

    void solve()
    {
        k = inicjuj();

        readK();

        listNode *acc = t.begin, *tmp;

        while (acc->nxt != NULL)
        {
            if (acc->val < acc->nxt->val)
                break;
            acc = acc->nxt;
        }

        while (true)
        {
            int in = wczytaj();

            if (in == 0) break;

            if (acc->nxt == NULL)
            {
                acc->val = max(acc->val, in);
                
                if (acc->prv != NULL)
                    acc = acc->prv;
            }
            else
            {
                tmp = acc->prv;

                t.remadd(acc, in);
                
                if (tmp == NULL) acc = t.begin;
                else acc = tmp;
            }

            while (acc->nxt != NULL)
            {
                if (acc->val < acc->nxt->val)
                    break;
                acc = acc->nxt;
            }
        }

        t.print();
    }
};
 
int main()
{
    sol::solve();
}