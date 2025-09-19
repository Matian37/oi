//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;

#define pbds __gnu_pbds
#define cxx __gnu_cxx
#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() chrono::high_resolution_clock::now().time_since_epoch().count()
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

namespace sol
{
    struct bigInt
    {
        string val;

        #define toInt(x) (int((x)-'0'))
        #define toChar(x) (char((x)+'0'))

        bigInt() : val("0") {};
        bigInt(string _val)
        {
            val = _val;
            reverse(all(val));
        }

        bigInt operator+(string a)
        {
            return *this + bigInt(a);
        }

        bigInt operator+(bigInt a)
        {
            string result = "";

            while (val.size() < a.val.size())
                val.push_back('0');
            while (a.val.size() < val.size())
                a.val.push_back('0');
            
            int rest = 0;

            for (int i = 0; i < isize(val); i++)
            {
                int value = toInt(val[i]) + toInt(a.val[i]) + rest;
                rest = value / 10;
                result += toChar(value % 10);
            }

            result += toChar(rest);

            while (val.size() > 1)
            {
                if (val.back() != '0') break;
                val.pop_back();
            }

            while (a.val.size() > 1)
            {
                if (a.val.back() != '0') break;
                a.val.pop_back();
            }

            while (result.size() > 1)
            {
                if (result.back() != '0') break;
                result.pop_back();
            }

            reverse(all(result));

            return bigInt(result);
        }

        bigInt operator-(string a)
        {
            return *this - bigInt(a);
        }

        bigInt operator-(bigInt a)
        {
            string result = "";

            while (val.size() < a.val.size())
                val.push_back('0');
            while (a.val.size() < val.size())
                a.val.push_back('0');
            
            int rest = 0;

            for (int i = 0; i < isize(val); i++)
            {
                int value = toInt(val[i]) - toInt(a.val[i]) - rest;

                if (value < 0)
                {
                    value += 10;
                    result += toChar(value);
                    rest = 1;
                }
                else
                {
                    result += toChar(value);
                    rest = 0;
                }
            }

            while (val.size() > 1)
            {
                if (val.back() != '0') break;
                val.pop_back();
            }

            while (a.val.size() > 1)
            {
                if (a.val.back() != '0') break;
                a.val.pop_back();
            }

            while (result.size() > 1)
            {
                if (result.back() != '0') break;
                result.pop_back();
            }

            reverse(all(result));

            return bigInt(result);
        }

        // "lazy" division
        int operator/(bigInt b)
        {
            bigInt r = *this;

            int c = 0;

            while (r >= b)
            {
                r = r - b;
                c++;
            }

            return c;
        }

        bool operator>=(bigInt a)
        {
            string sa = val, sb = a.val;

            if (sa.size() != sb.size())
                return sa.size() > sb.size();

            reverse(all(sa));
            reverse(all(sb));

            return sa >= sb;
        }

        string getString()
        {
            string c = val;
            reverse(all(c));
            return c;
        }
    };

    bigInt p3[128];

    using pbig = pair<bigInt, bigInt>;

    inline int getSegment(bigInt a, int k)
    {
        return (int)(1 + ((a - "1") / p3[k - 1]));
    }

    inline ii getSquare(pbig a, int k)
    {
        return {getSegment(a.first, k), getSegment(a.second, k)};
    }

    void jumpDown(pbig& l, ii sql, int k)
    {
        for (int j = 1; j < sql.first; j++)
            l.first = l.first - p3[k - 1];
        for (int j = 1; j < sql.second; j++)
            l.second = l.second - p3[k - 1];
    }

    void fa(string& s)
    {
        for (auto& i : s)
        {
            switch (i)
            {
                case 'E':
                    i = 'N';
                    break;
                case 'N':
                    i = 'E';
                    break;
                case 'S':
                    i = 'W';
                    break;
                default:
                    i = 'S';
                    break;
            }
        }
    }

    void fb(string& s)
    {
        for (auto& i : s)
        {
            switch (i)
            {
                case 'E':
                    i = 'S';
                    break;
                case 'N':
                    i = 'W';
                    break;
                case 'S':
                    i = 'E';
                    break;
                default:
                    i = 'N';
                    break;
            }
        }
    }

    void fc(string& s)
    {
        for (auto& i : s)
        {
            switch (i)
            {
                case 'E':
                    i = 'W';
                    break;
                case 'N':
                    i = 'S';
                    break;
                case 'S':
                    i = 'N';
                    break;
                default:
                    i = 'E';
                    break;
            }
        }
    }

    int getDistance(ii l, string& mp, ii start)
    {
        ii acc = start;

        int c = 0;

        for (auto i : mp)
        {
            if (acc == l) return c;

            c++;

            switch (i)
            {
                case 'N':
                    acc.second++;
                    break;
                case 'S':
                    acc.second--;
                    break;
                case 'E':
                    acc.first++;
                    break;
                default:
                    acc.first--;
                    break;
            }
        }

        return c;
    }

    ii getStart(string& mpch)
    {
        ii acc = {0, 0};

        for (auto i : mpch)
        {
            switch (i)
            {
                case 'N':
                    acc.second++;
                    break;
                case 'S':
                    acc.second--;
                    break;
                case 'E':
                    acc.first++;
                    break;
                default:
                    acc.first--;
                    break;
            }
        }

        if (acc.second == 0)
        {
            if (acc.first > 0) return {1, 1};
            return {3, 3};
        }

        if (acc.second > 0) return {1, 1};
        return {3, 3};
    }

    void doRotation(ii l, string& mpch, string& rt)
    {
        int pos = getDistance(l, mpch, getStart(mpch));

        switch (rt[pos])
        {
            case 'A':
                fa(mpch);
                break;
            case 'B':
                fb(mpch);
                break;
            case 'C':
                fc(mpch);
                break;
            default:
                break;
        }
    }

    bigInt solve(pbig l, int k)
    {
        bigInt result("0");

        string mpch = "EENNWSWN", rt = "AA000CBB0";

        while (k != 0)
        {
            auto sql = getSquare(l, k);
            int dist = getDistance(sql, mpch, getStart(mpch));

            for (int j = 0; j < dist; j++)
                result = result + p3[2 * (k - 1)];
            
            jumpDown(l, sql, k);
            doRotation(sql, mpch, rt);

            k--;
        }

        return result;
    }

    void read()
    {
        int k;
        string a1, a2, b1, b2;
        cin >> k >> a1 >> a2 >> b1 >> b2;

        p3[0].val = "1";

        for (int i = 1; i < 128; i++)
            for (int j = 0; j < 3; j++)
                p3[i] = p3[i] + p3[i - 1];

        pbig l = {bigInt(a1), bigInt(a2)},
             d = {bigInt(b1), bigInt(b2)};
        
        bigInt a = solve(l, k),
               b = solve(d, k);
        
        bigInt r = (b >= a ? b - a : a - b);

        cout << r.getString() << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
}