//Să se scrie un program pentru ordonarea descrescătoare a unui şir de n numere folosind
//metoda Quick - Sort.

#include <iostream>
using namespace std;

void quickSort(int[], int, int);
void print(int[], int);

int v[100], n;
int main() {
    cin>>n;
    for(int i=0; i<n; ++i) {
        cin>>v[i];
    }
    quickSort(v,0,n-1);
    print(v,n);
    return 0;
}

void quickSort(int v[100], int left, int right) {
    if(left < right) {
        int mij = (left + right) / 2;
        int aux = v[left];
        v[left] = v[mij];
        v[mij] = aux;

        int i = left, j = right, indice = 0;
        while(i < j) {
            if(v[i] < v[j]) {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                indice = 1 - indice;
            }
            i += indice;
            j -= 1-indice;
        }
        quickSort(v,left,i-1);
        quickSort(v, i+1, right);
    }
}

void print(int v[100], int n) {
    for(int i=0; i<n; ++i) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}