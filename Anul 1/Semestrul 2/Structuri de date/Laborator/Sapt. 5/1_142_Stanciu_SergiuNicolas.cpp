// Cerinta 1.1
// Să se creeze o listă ordonată crescător folosind operat, ii de insert, ie
// (nodul Head va retine elementul minim).

// Cerinta 1.2
// Implementat, i operat, ia de s,tergere a întregii liste.

// Cerinta 1.3
// Implementat, i operat, ia de s,tergere a unui element dat la tastatură
// dintr-o listă înlănt,uită oarecare (dacă el există).

#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* next;
}*start;

void afisare(Node*&);

// Problema 1_1
void insert_start(Node*& start, int value);
void insert_after(Node*& start, Node* olpd, int value);
void insert_end(Node*& start, int value);
void createList(Node*&, int);

// Problema 1_2
void delete_start(Node*&);
void delete_after(Node*);
void delete_end(Node*&);
void deleteList(Node*&, int);
void delete_element(Node*&, int);
int n, number;
int main() {

    cin>>n;
    createList(start, n);
    delete_element(start, 8);
    afisare(start);
//    deleteList(start, n);
    return 0;
}
void afisare(Node*& start) {
    for(Node* aux = start; aux != NULL ; aux =aux->next) {
        cout<<aux->value<<" ";
    }
}

void insert_start(Node*& start, int value) {
    Node* nodeToBeInserted = new Node;
    nodeToBeInserted->value = value;
    if(start == NULL) {
        nodeToBeInserted->next = NULL;
        start = nodeToBeInserted;
    } else {
        nodeToBeInserted->next = start;
        start = nodeToBeInserted;
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

void insert_after(Node*& start, Node* oldp, int value) {
    Node* nodeToBeInserted = new Node;
    nodeToBeInserted->value = value;
    nodeToBeInserted->next = oldp->next;
    oldp->next = nodeToBeInserted;
}

void createList(Node*& start, int n) {
    for(int i=0; i<n; ++i) {
        cin>>number;
        if(start == NULL || number <= start->value) {
            insert_start(start, number);
        } else {
            Node* aux = start;
            while(aux->next != NULL && number >= aux->next->value) {
                aux = aux->next;
            }
            if(aux->next == NULL) {
                insert_end(start, number);
            } else {
                insert_after(start, aux, number);
            }
        }
    }
}

// Problema 1_2
void delete_start(Node*& start) {
    Node* aux = start;
    start = start->next;
    delete aux;
}

void deleteList(Node*& start, int n) {
    for(int i=0; i<n; ++i) {
        delete_start(start);
    }
    if(start == NULL) {
        cout << "Lista a fost stearsa!" << endl;
    }
}

// Problema 1_3
void delete_element(Node*& start, int numberToBeDeleted) {
    Node* aux = start;
    if(aux->value == numberToBeDeleted) {
        if(aux->next == NULL) {
            delete aux;
        } else {
            start = start->next;
            delete aux;
        }
    } else {
        while(aux->next != NULL && aux->next->value != numberToBeDeleted) aux=aux->next;
        if(aux->next == NULL) {
            Node* aux_aux = aux->next;
            aux->next = NULL;
            delete aux_aux;
        } else {
            Node* aux_aux = aux->next;
            aux->next = aux_aux->next;
            delete aux_aux;
        }
    }

}
