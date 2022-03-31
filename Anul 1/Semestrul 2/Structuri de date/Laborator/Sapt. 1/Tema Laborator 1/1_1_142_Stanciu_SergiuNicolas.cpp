//Să se scrie un program pentru ordonarea crescătoare a unui şir de n
//numere folosind metoda Bubble – Sort (sortarea prin interschimbare).

#include <iostream>
using namespace std;
int n, a[10000];
int main()
{
    cin>>n;
    for(int i=0; i<n; ++i){
        cin>>a[i];
    }

    for(int i=0; i<n-1; ++i) {
        for(int j=i+1; j<n; ++j) {
            if(a[i] > a[j]) {
                swap(a[i], a[j]);
            }
        }
    }
    for(int i=0; i<n; ++i) {
        cout<<a[i]<<" ";
    }

    return 0;
}