#include <bits/stdc++.h>

using namespace std;

struct Point
{
    double x, y;
    Point(){};
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};
namespace location
{
    enum LOCATION
    {
        INSIDE,
        OUTSIDE,
        BOUNDARY
    };
}

double determinant(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
    return a11 * a22 * a33 + a21 * a32 * a13 + a31 * a12 * a23 - a13 * a22 * a31 - a23 * a32 * a11 - a33 * a12 * a21;
}

location::LOCATION checkLocation(Point a, Point b, Point c, Point d)
{
    double a1 = a.x * a.x + a.y * a.y;
    double b1 = b.x * b.x + b.y * b.y;
    double c1 = c.x * c.x + c.y * c.y;
    double d1 = d.x * d.x + d.y * d.y;

    double det1 = a.x * determinant(b.y, b1, 1, c.y, c1, 1, d.y, d1, 1);
    double det2 = (-1) * a.y * determinant(b.x, b1, 1, c.x, c1, 1, d.x, d1, 1);
    double det3 = a1 * determinant(b.x, b.y, 1, c.x, c.y, 1, d.x, d.y, 1);
    double det4 = (-1) * determinant(b.x, b.y, b1, c.x, c.y, c1, d.x, d.y, d1);

    det1 = abs(det1) == 0.0 ? 0.0 : det1;
    det2 = abs(det2) == 0.0 ? 0.0 : det2;
    det3 = abs(det3) == 0.0 ? 0.0 : det3;
    det4 = abs(det4) == 0.0 ? 0.0 : det4;

    double res = det1 + det2 + det3 + det4;

    if (res == 0)
    {
        return location::BOUNDARY;
    }
    else if (res > 0)
    {
        return location::INSIDE;
    }
    return location::OUTSIDE;
}
int main()
{
    int n;
    vector<location::LOCATION> res;
    Point a, b, c;

    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        Point aux;
        cin >> aux.x >> aux.y;
        res.push_back(checkLocation(a, b, c, aux));
    }

    for (auto &re : res)
    {
        if (re == location::INSIDE)
        {
            cout << "INSIDE\n";
        }
        else if (re == location::OUTSIDE)
        {
            cout << "OUTSIDE\n";
        }
        else
        {
            cout << "BOUNDARY\n";
        };
    }
    return 0;
}