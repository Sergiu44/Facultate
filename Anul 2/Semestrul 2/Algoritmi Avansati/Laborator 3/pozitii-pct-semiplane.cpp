#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#define INF 999999999

using namespace std;

struct Semiplan
{
    double a, b, c;
};

struct Inequality
{
    double x, y;
};

vector<Inequality> inec;
vector<Semiplan> v;
vector<double> max_x, min_x, max_y, min_y;
vector<pair<double, double>> Q;
long n, m;

void resInequality(Semiplan s, long i)
{
    if (s.b == 0)
    {
        inec[i].y = 0;
        inec[i].x = -s.c / s.a;
        if (s.a < 0)
        {
            min_x.push_back(inec[i].x);
        }
        else
        {
            max_x.push_back(inec[i].x);
        }
    }
    else
    {
        inec[i].x = 0;
        inec[i].y = -s.c / s.b;
        if (s.b < 0)
        {
            min_y.push_back(inec[i].y);
        }
        else
        {
            max_y.push_back(inec[i].y);
        }
    }
}

double isInsideIntersection(pair<double, double> point)
{
    long i_max_x = 0, i_max_y = 0, i_min_x = 0, i_min_y = 0;
    long xmax = max_x.size(), xmin = min_x.size(), ymax = max_y.size(), ymin = min_y.size();
    if (!xmax || !xmin || !ymax || !ymin)
        return 0;
    while (point.first >= max_x[i_max_x] && i_max_x <= xmax)
        i_max_x++;
    while (point.second >= max_y[i_max_y] && i_max_y <= ymax)
        i_max_y++;
    while (point.first <= min_x[i_min_x] && i_min_x <= xmin)
        i_min_x++;
    while (point.second <= min_y[i_min_y] && i_min_y <= ymin)
        i_min_y++;

    if (i_max_x >= xmax || i_max_y >= ymax || i_min_x >= xmin || i_min_y >= ymin)
        return 0;
    else
    {
        return ((max_x[i_max_x] - min_x[i_min_x]) * (max_y[i_max_y] - min_y[i_min_y]));
    }
}

int main()
{

    cin >> n;
    v.resize(n);
    inec.resize(n);
    for (long i = 0; i < n; i++)
    {
        cin >> v[i].a >> v[i].b >> v[i].c;
        inec[i].x = 0;
        inec[i].y = 0;
    }
    cin >> m;
    Q.resize(m);
    for (long i = 0; i < m; i++)
        cin >> Q[i].first >> Q[i].second;

    for (long i = 0; i < n; i++)
        resInequality(v[i], i);

    sort(max_x.begin(), max_x.end());
    sort(max_y.begin(), max_y.end());

    sort(min_x.begin(), min_x.end(), greater<>());
    sort(min_y.begin(), min_y.end(), greater<>());

    for (long i = 0; i < m; i++)
    {
        double rez = isInsideIntersection(Q[i]);
        if (rez != 0)
            cout << "YES" << endl
                 << fixed << setprecision(6) << rez << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}