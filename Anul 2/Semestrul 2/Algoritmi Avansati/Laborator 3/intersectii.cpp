#include <iostream>
#include <algorithm>
#include <vector>
#define INF 999999999

using namespace std;

struct Semiplan
{
    double a, b, c;
};

struct Inequality
{
    double x, y;
    bool x_max, y_max;
};

vector<Inequality> ineq;
vector<Semiplan> v;
double n;

void read()
{
    cin >> n;
    v.resize(n);
    ineq.resize(n);
    for (double i = 0; i < n; i++)
    {
        cin >> v[i].a >> v[i].b >> v[i].c;
        if (v[i].b == 0)
        {
            ineq[i].y = 0;
            ineq[i].x = -v[i].c / v[i].a;
            if (v[i].a < 0)
            {
                ineq[i].x_max = false;
            }
            else
            {
                ineq[i].x_max = true;
            }
        }
        else
        {
            ineq[i].x = 0;

            ineq[i].y = -v[i].c / v[i].b;
            if (v[i].b < 0)
            {
                ineq[i].y_max = false;
            }
            else
            {
                ineq[i].y_max = true;
            }
        }
    }
}

void max_min_x_y(double &max_x, double &min_x, double &max_y, double &min_y)
{

    for (long i = 0; i < n; i++)
    {
        if (v[i].b == 0)
        {
            if (ineq[i].x_max)
            {
                if (max_x < ineq[i].x)
                    max_x = ineq[i].x;
            }
            else
            {
                if (min_x > ineq[i].x)
                    min_x = ineq[i].x;
            }
        }
        else
        {
            if (ineq[i].y_max)
            {
                if (max_y < ineq[i].y)
                    max_y = ineq[i].y;
            }
            else
            {
                if (min_y > ineq[i].y)
                    min_y = ineq[i].y;
            }
        }
    }
}

int main()
{

    read();

    double Xmaxim = -INF;
    double Xminim = INF;

    double Ymaxim = -INF;
    double Yminim = INF;

    max_min_x_y(Xmaxim, Xminim, Ymaxim, Yminim);

    if (Xminim == INF)
    {
        Xminim = -INF;
    }
    if (Xmaxim == -INF)
    {
        Xmaxim = INF;
    }
    if (Yminim == INF)
    {
        Yminim = -INF;
    }
    if (Ymaxim == -INF)
    {
        Ymaxim = INF;
    }

    if (Xminim < Xmaxim && Yminim < Ymaxim)
    {
        if (Xmaxim == INF || Xminim == -INF || Ymaxim == INF || Yminim == -INF)
            cout << "UNBOUNDED";
        else
            cout << "BOUNDED";
    }
    else
    {
        if (Xminim < Xmaxim || Yminim < Ymaxim)
        {
            cout << "VOID";
        }
    }
    return 0;
}