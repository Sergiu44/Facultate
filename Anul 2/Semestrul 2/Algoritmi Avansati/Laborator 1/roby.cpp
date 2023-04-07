#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int nr_touch, nr_right, nr_left;

void checkDetValue(pair<long, long> x, pair<long, long> y, pair<long, long> z)
{
    long sum = y.first * z.second + x.first * y.second + z.first * x.second - x.second * y.first - z.first * y.second - x.first * z.second;
    if (sum == 0)
    {
        ++nr_touch;
    }
    else if (sum < 0)
    {
        ++nr_right;
    }
    else
    {
        ++nr_left;
    }
}
int main()
{
    long n;

    cin >> n;

    pair<long, long> x, y, z;
    cin >> x.first >> x.second >> y.first >> y.second >> z.first >> z.second;
    pair<long, long> aux1 = x;
    checkDetValue(x, y, z);

    int i = 3;
    do
    {
        x = y;
        y = z;
        cin >> z.first >> z.second;
        checkDetValue(x, y, z);
        ++i;
    } while (i < n);

    checkDetValue(y, z, aux1);
    cout << nr_left << " " << nr_right << " " << nr_touch << endl;
    return 0;
}