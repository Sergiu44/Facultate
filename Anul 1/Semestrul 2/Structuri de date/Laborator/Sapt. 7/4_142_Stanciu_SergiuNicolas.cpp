#include <iostream>

using namespace std;

struct Element {
    int linie;
    int coloana;
    Element* next;
}*front,*rear;
// -> front represents the head of the queue and rear represents the element at the bottom of the queue
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};
void fillMatrix(int[100][100], int, int, int);
void push(int, int);
void afisare();

int m, n, a[100][100];
int main() {
    int count = 2;
    cin>>m>>n;
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
        cin>>a[i][j];

    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            if(a[i][j] == 1) {
                fillMatrix(a, i, j, count);
                ++count;
                rear = front = NULL;
            }
        }
    }
    cout<<endl<<endl;
    afisare();
    return 0;
}

void fillMatrix(int a[100][100], int i_st, int j_st, int count) {
    push(i_st, j_st);
    a[i_st][j_st] = count;
    while(rear && front) {
        int i = rear->linie; int j = rear->coloana;
        for(int k = 0; k < 4; ++k) {
            int i_next = i + di[k]; int j_next = j + dj[k];
            if(i_next >= 0 && j_next >= 0 && i_next <= m-1 && j_next <= n-1 && a[i_next][j_next] == 1) {
                a[i_next][j_next] = count;
                push(i_next, j_next);
            }
        }
        Element* aux = rear;
        rear = rear->next;
        delete aux;
    }
}

void push(int linie, int coloana) {
    Element* element = new Element;
    element->linie = linie;
    element->coloana = coloana;

    if(rear == NULL) {
        rear = front = element;
        element->next = NULL;
    } else {
        front->next = element;
        front = element;
        element->next = NULL;
    }
}

void afisare() {
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}