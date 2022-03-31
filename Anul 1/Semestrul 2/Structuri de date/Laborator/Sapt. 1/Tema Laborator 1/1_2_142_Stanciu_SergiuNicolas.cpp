//Să se scrie un program pentru ordonarea crescătoare a unui şir de n
//numere folosind sortarea prin inserţie (Insertion Sort).

#include <iostream>

using namespace std;

int n, a[10000];
int main()
{
    cin>>n;
    for(int i=0; i<n; ++i){
        cin>>a[i];
    }
    for(int i=1; i<n; ++i) {
        int aux = i;
        while(a[i] < a[i-1] && i>0) {
            swap(a[i],a[i-1]);
            --i;
        }
        i = aux;


    }
    for(int i=0; i<n; ++i) {
        cout<<a[i]<<" ";
    }

    return 0;
}