#include <iostream>
using namespace std;

template <typename T>
struct ListNode {
    T val;
    ListNode* next;
    ListNode* prev;
    ListNode(T v) : val(v), next(nullptr), prev(nullptr) {}
};

template <typename T>
class CircularDoublyLinkedList {
private:
    ListNode<T>* head;

public:
    CircularDoublyLinkedList() : head(nullptr) {}

    T front();
    T back();
    void push_front(T x);
    void push_back(T x);
    T pop_front();
    T pop_back();
    void insert(T x, int pos);
    void remove(int pos);
    T operator[](int pos);
    bool empty();
    int size();
    void clear();
    void reverse();
};


template <typename T>
T CircularDoublyLinkedList<T>::front(){
    if (head == nullptr){
        throw runtime_error("Empty");
    };
    return head->val;
};

template <typename T>
T CircularDoublyLinkedList<T>::back(){
    if (head == nullptr){
        throw runtime_error("Empty");
    };
    return head->prev->val;
}

template <typename T>
void CircularDoublyLinkedList<T>::push_front(T x) {
    ListNode<T>* nd = new ListNode<T>(x);

    if (head == nullptr) {
        nd->next = nd;
        nd->prev = nd;
        head = nd;
        return;
    }
    ListNode<T>* tail = head->prev;
    nd->next = head;
    nd->prev = tail;
    tail->next = nd;
    head->prev = nd;
    head = nd;
}

template <typename T>
void CircularDoublyLinkedList<T>::push_back(T x){
    ListNode<T>* nd = new ListNode<T>(x);

    if (head == nullptr) {
        nd->next = nd;
        nd->prev = nd;
        head = nd;
        return;
    }
    ListNode<T>* tail = head->prev;
    nd->next = head;
    nd->prev = tail;
    tail->next = nd;
    head->prev = nd;
}

template <typename T>
T CircularDoublyLinkedList<T>::pop_front(){
    if(head == nullptr) {
        throw runtime_error("Empty");
    }

    T valor = head->val;
    if(head->next == head) {
        delete head;
        head = nullptr;
    }else {
        ListNode<T>* tail = head->prev;
        ListNode<T>* temp = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete temp;
    }
    return valor;
}

template <typename T>
T CircularDoublyLinkedList<T>::pop_back() {
    if(head == nullptr) {
        throw runtime_error("Empty");
    }

    ListNode<T>* tail = head->prev;
    T valor = tail->val;
    if(tail==head) {
        delete head;
        head = nullptr;
    }else {
        ListNode<T>* ntail = tail->prev;
        ntail->next = head;
        head->prev = ntail;
        delete tail;
    }
    return valor;
}

template <typename T>
void CircularDoublyLinkedList<T>::insert(T valor, int pos) {
    if (pos < 0) {
        throw out_of_range("Numero Negativo");
    }

    if(head == nullptr) {
        if(pos == 0) {
            push_back(valor);
            return;
        }
        throw out_of_range("Fuera de rango");
    }

    if(pos == 0) {
        push_front(valor);
        return;
    }

    ListNode<T>* actual = head;
    int i = 0;
    while(i <pos && actual->next != head) {
        actual = actual->next;
        i++;
    }


    if(i == pos) {
        ListNode<T>* n = new ListNode<T>(valor);
        ListNode<T>* ant = actual->prev;
        ant->next = n;
        n->prev = ant;
        n->next = actual;
        actual->prev = n;
        return;
    }

    if(actual->next == head && i + 1 == pos) {
        push_back(valor);
        return;
    }

    throw out_of_range("Fuera de rango");
}

template <typename T>
void CircularDoublyLinkedList<T>::remove(int pos) {
    if(head == nullptr) {
        throw runtime_error("Empty");
    }
    if (pos < 0) {
        throw out_of_range("Numero Negativo");
    }

    if(pos == 0) {
        pop_front();
        return;
    }

    ListNode<T>* actual = head;
    int i = 0;
    while(i < pos && actual->next != head) {
        actual = actual->next;
        i++;
    }
    if(i <pos) {
        out_of_range("Fuera de rango");
    }
    if(actual->next == head) {
        pop_back();
        return;
    }

    ListNode<T>* prev = actual->prev;
    ListNode<T>* next = actual->next;
    prev->next = next;
    next->prev = prev;
    delete actual;
}

template <typename T>
bool CircularDoublyLinkedList<T>::empty(){
    return head == nullptr;
};

template <typename T>
T CircularDoublyLinkedList<T>::operator[](int pos) {
    if (pos < 0) {
        throw out_of_range("Numero Negativo");
    }
    if(head == nullptr) {
        throw runtime_error("Empty");
    }

    ListNode<T>* actual = head;
    int i = 0;

    while(i < pos && actual->next != head) {
        actual = actual->next;
        i++;
    }

    if(i == pos) {
        return actual->val;
    }

    throw out_of_range("Fuera de rango");
}

template <typename T>
int CircularDoublyLinkedList<T>::size() {
    if(head == nullptr) {
        return 0;
    }

    int count = 1;
    ListNode<T>* actual = head->next;
    while(actual != head) {
        count++;
        actual = actual->next;
    }
    return count;
}

template <typename T>
void CircularDoublyLinkedList<T>::clear() {
    if (head == nullptr) {
        return;
    }

    ListNode<T>* actual = head->next;
    while (actual != head) {
        ListNode<T>* temp = actual;
        actual = actual->next;
        delete temp;
    }
    delete head;
    head = nullptr;
}

template <typename T>
void CircularDoublyLinkedList<T>::reverse() {
    if(head == nullptr || head->next == head) {
        return;
    }
    ListNode<T>* actual = head;
    do {
        ListNode<T>*temp = actual->next;
        actual->next = actual->prev;
        actual->prev = temp;
        actual = temp;
    }while(actual != head);
    head = head->next;
}



