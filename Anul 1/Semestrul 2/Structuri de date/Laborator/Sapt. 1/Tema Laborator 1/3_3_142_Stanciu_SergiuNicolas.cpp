//Se dă un s, ir ordonat crescător cu n elemente care a fost rotit de un număr necunoscut de ori.
//Să se scrie un algoritm de complexitate O(logn) pentru căutarea unui număr în vector.

#include <iostream>

using namespace std;

int n, a[100], x;

int binary(int *a, int st, int dr, int x) {
    if (st > dr) {
        return -1;
    }
    int mij = (st + dr) / 2;
    if(a[mij] == x) {
        return mij+1;
    }

    if(a[st] <= a[mij]) {
        if(x >= a[st] && x<= a[mij]) {
            return binary(a,st, mij-1, x);
        }
        return binary(a, mij+1, dr, x);
    }

    if(x >= a[mij] && x <= a[dr]) {
        return binary(a,mij+1, dr, x);
    }
    return binary(a, st, mij-1, x);
}

int main()
{
    cin>>n>>x;
    for(int i=0; i < n; ++i) {
        cin >> a[i];
    }
    int index = binary(a,0,n-1,x);
    cout<<index-1<<endl;
    return 0;
}