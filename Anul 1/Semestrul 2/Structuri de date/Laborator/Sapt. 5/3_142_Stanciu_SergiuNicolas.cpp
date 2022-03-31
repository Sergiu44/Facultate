// Să se implementeze cu ajutorul unei
// liste liniare simplu înlănţuită alocată dinamic un polinom de grad n. Fiecare nod se va considera că reţine gradul fiecărui monom, precum şi coeficientul său. Structura poate fi definită
// astfel:
// struct Node {
//      int Grade, Coef;
//      Node *Next;
//};

// Fiind date polinoamele P s, i Q de grad n, respectiv m, reprezentate ca mai sus, să se scrie
// câte un program care calculează s, i afis,ează:
// 3.1) Polinomul rezultat prin înmult, irea polinomului P cu scalarul a (număr real nenul);
// 3.2) P(x0) (evaluarea polinomului P într-un punct dat x0);
// 3.3) Suma polinoamelor P s, i Q.

#include <iostream>
#include <cmath>
using namespace std;

struct Polinom {
        int grade;
        int coef;
        Polinom* next;
}*P,*Q;

void citirePolinom(Polinom*&);
void insert_end(Polinom*&, int, int);
void afisareScalar(Polinom*&, int);
int calcularePunct(Polinom*&, int);
void sumaPolinoame(Polinom*&, Polinom*&);
int number, x0;
int main() {
    // 3.1
    cout<<"Primul polinom"<<endl;
    citirePolinom(P);
    cout<<endl<<"Al doilea polinom"<<endl;
    citirePolinom(Q);
    cout<<endl;
    cout<<"Coeficientul care va fi inmultit cu polinomul P: ";
    cin>>number;
    afisareScalar(P,number);
    cout<<endl;

    // 3.2
    cout<<"Punctul x0: "; cin>>x0;
    cout<<"Rezultatul polinomului in punctul "<<x0<<" este: "<<calcularePunct(P,x0)<<endl;
    cout<<endl;

    // 3.3
    sumaPolinoame(P,Q);


    return 0;
}

void citirePolinom(Polinom*& polinom) {
    int coef, grade;
    cin>>grade>>coef;
    while(grade>=0) {
        insert_end(polinom, grade, coef);
        cin>>grade>>coef;
    }
}

void insert_end(Polinom*& start, int grade, int coef) {
    Polinom* polinom = new Polinom;
    polinom->next = NULL;
    polinom->grade = grade;
    polinom->coef = coef;

    if(start == NULL) {
        start = polinom;
    } else {
        Polinom* aux = start;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next=polinom;
    }
}

void afisareScalar(Polinom*& polinom, int number) {
    for(Polinom* aux = polinom; aux != NULL; aux=aux->next) {
        cout<<aux->grade<<" "<<aux->coef*number<<endl;
    }
    cout<<endl;
}

int calcularePunct(Polinom*& polinom, int pct) {
    int rez = 0;
    for(Polinom* aux = polinom; aux != NULL; aux=aux->next) {
        rez += pow(pct, aux->grade) * aux->coef;
    }
    return rez;
}

void sumaPolinoame(Polinom*& polinom1, Polinom*& polinom2) {
    cout<<"Suma celor doua polinoame este: "<<endl;
    for(Polinom* aux1 = polinom1; aux1 != NULL; aux1 = aux1->next) {
        bool ok = false;
        for(Polinom* aux2 = polinom2; aux2 != NULL; aux2 = aux2->next) {
            if(aux2->grade == aux1->grade) {
                ok = true;
                cout<<"Gradul "<<aux2->grade<<" si coeficientul "<<aux1->coef+aux2->coef<<endl;
            }
        }
        if(!ok) {
            cout<<"Gradul "<<aux1->grade<<" si coeficientul "<<aux1->coef<<endl;
        }
    }
    for(Polinom* aux2 = polinom2; aux2 != NULL; aux2 = aux2->next) {
        bool ok = false;
        for(Polinom* aux1 = polinom1; aux1 != NULL; aux1 = aux1->next) {
            if(aux2->grade == aux1->grade) {
                ok = true;
            }
        }
        if(!ok) {
            cout<<"Gradul "<<aux2->grade<<" si coeficientul "<<aux2->coef<<endl;
        }
    }
}
