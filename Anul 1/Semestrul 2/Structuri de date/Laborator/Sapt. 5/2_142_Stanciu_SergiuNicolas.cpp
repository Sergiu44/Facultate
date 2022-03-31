// Se consideră două numere reprezentate într-o listă înlănt,uită în care fiecare nod reprezintă o cifră. Cifrele sunt ret, inute în
// ordine inversă astfel încât cifra unităt, ilor să fie stocată la începutul listei . Să se scrie un
// program C/C++ care să calculeze suma acestor numere.
// Exemplu:
// Input: (1 -> 5 -> 3), (2 -> 6 -> 4)
// Output: 813

#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* next;
}*first,*second;

void insert_end(Node*&, int);
void readList(Node*&);
void afisare(Node*&);

int main() {
    readList(first);
    readList(second);
    Node* aux1 = first;
    Node* aux2 = second;
    int count = 0;
    int numberToShow = 0, p=1;
    while(aux1 != NULL || aux2 != NULL) {
        if(aux1 == NULL) {
            numberToShow = (aux2->value+count)%10*p + numberToShow;
            count = (aux2->value+count)/10;
            aux2=aux2->next;
            p=p*10;
        } else if(aux2 == NULL) {
            numberToShow = (aux1->value+count)%10*p + numberToShow;
            count = (aux1->value+count)/10;
            aux1=aux1->next;
            p=p*10;
        } else {
            numberToShow = (aux1->value+aux2->value+count)%10*p + numberToShow;
            count = (aux1->value+aux2->value+count)/10;
            aux1=aux1->next;
            aux2=aux2->next;
            p=p*10;
        }
    }
    if(count) {
        cout<<p*count+numberToShow<<endl;
    } else {
        cout<<numberToShow<<endl;
    }
    return 0;
}

void readList(Node*& node) {
    int number;
    cin>>number;
    while(number) {
        int cif = number % 10;
        insert_end(node, cif);
        number /= 10;
    }
}

void insert_end(Node*& start, int value) {
    Node* nodeToBeInserted = new Node;
    nodeToBeInserted->next = NULL;
    nodeToBeInserted->value = value;
    if(start == NULL) {
        start = nodeToBeInserted;
    } else {
        Node* aux = start;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next=nodeToBeInserted;
    }
}

void afisare(Node*& start) {
    for(Node* aux = start; aux != NULL ; aux =aux->next) {
        cout<<aux->value<<" ";
    }
}
