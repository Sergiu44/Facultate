#include <iostream>

using namespace std;

struct Pini {
    int value;
    Pini* next;
}*start, *finish;

void push(Pini*&, Pini*&, int);
void pop(Pini*&, Pini*&);

int n;
int pereche[100];
int main() {

    cin>>n;
    for(int i=0; i<n; ++i) {
        cin>>pereche[i];
        if(start == NULL || finish->value != pereche[i]) {
            push(start, finish, pereche[i]);
        } else if(finish->value == pereche[i]) {
            pop(start, finish);
        }
    }
    if(start == NULL) {
        cout<<"Pinii pot fi conectati!"<<endl;
    } else {
        cout<<"Pinii nu pot fi conectati!"<<endl;
    }
    return 0;
}

void push(Pini*& start, Pini*& end, int value) {
    Pini* pini = new Pini;
    pini->value = value;
    if(start == NULL) {
        pini->next = NULL;
        start = end = pini;
    } else {
        pini->next = NULL;
        end->next = pini;
        end = pini;
    }
}

void pop(Pini*& start, Pini*& end) {
    if(start == NULL) {
        return;
    } else if (start->next == NULL) {
        start = NULL;
    } else if (start->next != NULL) {
        Pini* aux = start;
        while(aux->next != end) aux=aux->next;
        aux->next = NULL;
        delete end;
        end = aux;
    }
}