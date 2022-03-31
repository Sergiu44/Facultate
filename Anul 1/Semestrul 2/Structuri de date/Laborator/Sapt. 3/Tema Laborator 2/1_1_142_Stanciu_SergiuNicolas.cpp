//Să se scrie un program pentru ordonarea crescătoare a unui şir de n numere folosind metoda
//Merge – Sort.

#include <iostream>

using namespace std;
int n, v[100];

void print(int[]);
void mergeSort(int[],int,int);
void interclasare(int[],int,int,int);

int main() {
    cin>>n;
    for(int i=0; i<n; ++i) {
        cin>>v[i];
    }

    mergeSort(v,0,n-1);
    print(v);
    return 0;
}

void print(int v[100]) {
    for(int i=0; i<n; ++i) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void mergeSort(int v[100], int left, int right) {
    if(left>=right)
        // Oprim ciclul recursiv
        return;
    else {
        int mij = (left+right)/2;
        mergeSort(v,left,mij);
        mergeSort(v,mij+1,right);
        interclasare(v,left,mij, right);
    }
}

void interclasare(int v[100], int left, int mij, int right) {
    // Initializam lungimile celor doua array-uri
    int lengthLeftArray = mij-left+1;
    int lengthRightArray = right-mij;

    // Initializam array-urile pentru interclasare
    int leftArray[lengthLeftArray];
    int rightArray[lengthRightArray];
    for(int i = 0; i< lengthLeftArray; ++i) {
        leftArray[i] = v[i+left];
    }
    for(int i = 0; i< lengthRightArray; ++i) {
        rightArray[i] = v[i+mij+1];
    }

    // i -> indexul de inceput pentru array-ul din stanga
    // j -> indexul de inceput pentru array-ul din dreapta
    // leftIndex -> indexul de inceput pentru array-ul din stanga din array-ul initial
    int i=0, j=0, leftIndex = left;

    // Interclasare
    while(i < lengthLeftArray && j < lengthRightArray) {
        if(leftArray[i] <= rightArray[j]) {
            v[leftIndex] = leftArray[i];
            ++i;
        } else {
            v[leftIndex] = rightArray[j];
            ++j;
        }
        ++leftIndex;
    }

    while(i < lengthLeftArray) {
        v[leftIndex] = leftArray[i];
        ++i;
        ++leftIndex;
    }

    while(j < lengthRightArray) {
        v[leftIndex] = rightArray[j];
        ++j;
        ++leftIndex;
    }
}
