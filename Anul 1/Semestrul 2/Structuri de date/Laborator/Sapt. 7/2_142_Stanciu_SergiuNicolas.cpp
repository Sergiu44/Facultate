#include <iostream>
#include <cstring>
using namespace std;

struct Stack {
    int value;
    Stack* next;
}*top;

void push(Stack*&, int);
void calculate_stack(Stack*&, int);
char str[101];

int main() {
    cin.getline(str, 101);
    int count = 0;
    for(int i = 0; i<strlen(str); ++i) {
        int ok=1;
        int number = 0;
        if(isdigit(str[i])) {
            if(str[i-1] == '+' && !isdigit(str[i-2])) {
                cout<<"Expresia nu este valida!"<<endl;
                return 0;
            }
            if(str[i-1] == '-') {
                ok=-1;
            }
            while(isdigit(str[i])) {
                number = number*10 + (str[i] - '0');
                ++i;
            }
            number = number * ok;
            push(top, number);
            ++count;
        } else if(str[i] == ')') {
            calculate_stack(top, count);
        }
    }
    if(count) calculate_stack(top, count);
    if(top != NULL) cout<<top->value<<endl;
    else cout<<"Expresia nu este valida!"<<endl;
    return 0;
}

void push(Stack*& top, int value) {
    Stack* element = new Stack;
    element->value = value;
    if(top == NULL) {
        element->next = NULL;
        top = element;
    } else {
        element->next = top;
        top = element;
    }
}

void calculate_stack(Stack*& top, int count) {
    Stack* aux = top;
    int rez = 0;
    for(int i=0; i<count; ++i, aux=aux->next) {
        rez += aux->value;
    }
    push(top, rez);
}