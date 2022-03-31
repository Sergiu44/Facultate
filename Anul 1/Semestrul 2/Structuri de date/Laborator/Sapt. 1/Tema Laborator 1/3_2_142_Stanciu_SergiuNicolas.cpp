//Un circ include în programul său un număr în care acrobat, ii stau unul deasupra celuilalt pe
//umerii anteriorului. Din motive practice, fiecare persoană trebuie să fie mai scundă si mai
//usoară decât persoana de dedesubt. Fiind date greutătile si înăltimile persoanelor din circ,
//să se scrie un algoritm pentru a calcula cea mai lungă secventă posibilă dintr-un astfel de
//turn uman

#include <iostream>

using namespace std;
int n, x, y, matrix[2][100];
int main() {
    cin>>n;
    for(int i=0; i<n; ++i) {
        cin>>matrix[0][i]>>matrix[1][i];
    }

    for(int i=0; i<n-1; ++i) {
        for(int j=i+1; j<n; ++j) {
            if(matrix[0][j] > matrix[0][i]) {
                swap(matrix[0][j], matrix[0][i]);
                swap(matrix[1][j], matrix[1][i]);
            }
            else if(matrix[0][j] == matrix[0][i] && matrix[1][j] > matrix[1][i]) {
                swap(matrix[0][j], matrix[0][i]);
                swap(matrix[1][j], matrix[1][i]);
            }
        }
    }

    int count = 0;
    int index = 0;
    for(int i=1; i<n; ++i) {
        if((matrix[0][index] >= matrix[0][i]) || (matrix[0][index] == matrix[0][i] && matrix[1][index] >= matrix[1][i])) {
            ++count;
            index = i;
        }
    }

    cout<<count<<endl;

    return 0;
}