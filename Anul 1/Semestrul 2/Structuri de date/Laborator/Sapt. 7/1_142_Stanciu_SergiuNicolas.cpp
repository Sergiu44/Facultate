#include <iostream>
using namespace std;

struct PrioQueue {
    int value;
    unsigned int priority;
    PrioQueue* next;
}*q;

void push(int, int, PrioQueue*&);
void pop(PrioQueue*&, int);
void afisare(PrioQueue*&);

int x, y;
int main() {
    cin>>x>>y;
    push(x,1,q);
    push(y,1,q);
    push(10,3,q);
    push(1,2,q);
    push(2,2,q);
    push(7,2,q);
    afisare(q);
    pop(q, 3);
    afisare(q);
    return 0;
}

void push (int x, int prio, PrioQueue*& queue) {
    PrioQueue* newElem = new PrioQueue;
    newElem->value = x;
    newElem->priority = prio;
    if(queue == NULL) {
        newElem->next = NULL;
        queue = newElem;
    } else if(newElem->priority < queue->priority) {
        newElem->next = queue;
        queue = newElem;
    } else {
        PrioQueue* aux = queue;
        while(aux->next != NULL && (aux->priority != prio && aux->next->priority <= prio)) {
            aux = aux->next;
        }
        if(aux->next == NULL) {
            aux->next = newElem;
            newElem->next = NULL;
        } else {
            newElem->next = aux->next;
            aux->next = newElem;
        }
    }
}

void pop(PrioQueue*& queue, int prio) {
    PrioQueue* aux = queue;
    if(prio<queue->priority) {
        cout<<"Nu exista aceasta prioritate."<<endl;
        return;
    } else {
        while(aux->next->next != NULL && aux->next->next->priority <= prio) {
            aux = aux->next;
        }
        cout<<aux->value<<"     "<<aux->next->value<<endl;
        if(aux->next->next == NULL) {
            if(aux->next->priority != prio) {
                cout<<"Nu exista aceasta prioritate."<<endl;
                return;
            }
            PrioQueue* element = aux->next;
            aux->next = NULL;
            delete element;
        } else {
            PrioQueue* element = aux->next;
            aux->next = element->next;
            delete element;
        }
    }
}

void afisare(PrioQueue*& q) {
    if(q == NULL) {
        cout<<"Lista este vida"<<endl;
        return;
    }
    for(PrioQueue* aux = q; aux != NULL; aux=aux->next) {
        cout<<aux->value<<" "<<aux->priority<<endl;
    }
    cout<<endl;
}