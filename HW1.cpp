#include <iostream>
#include <vector>
#include <string>
using namespace std;


template <typename T>
struct ListNode{
    T val;
    ListNode* next;
    ListNode(T v) : val(v), next(nullptr) {}
};

template <typename T>
class ForwardList{
  private:
    ListNode<T>* head;

  public:
    ForwardList() : head(nullptr) {}

    T front();
    T back();
    void push_front(T x);
    void push_back(T x);
    T pop_front();
    T pop_back();
    T operator[](int pos);
    bool empty();
    int size();
    void clear();
    void sort();
    void reverse();
};

template <typename T>
T ForwardList<T>::front(){
    if (head == nullptr){
      throw runtime_error("Empty");
    };
    return head->val;
};

template <typename T>
T ForwardList<T>::back() {
    if (head == nullptr){
        throw runtime_error("Empty");
    };
    ListNode<T>* actual = head;
    while(actual->next != nullptr) {
        actual = actual->next;
    }
    return actual->val;
};

template <typename T>
void ForwardList<T>::push_front(T x) {
    ListNode<T>* nodo = new ListNode<T>(x);
    nodo->next = head;
    head = nodo;
};

template <typename T>
void ForwardList<T>::push_back(T x) {
    ListNode<T>* nodo = new ListNode<T>(x);
    if (head == nullptr) {
        head = nodo;
        return;
    }

    ListNode<T>* actual = head;
    while(actual->next != nullptr) {
        actual = actual->next;
    }
    actual->next = nodo;
};

template <typename T>
T ForwardList<T>::pop_front() {
    if(head == nullptr){
        throw runtime_error("Empty");
    };
    ListNode<T>* temp = head;
    T valor = head->val;
    head = head->next;
    delete temp;
    return valor;
};

template <typename T>
T ForwardList<T>::pop_back() {
    if (head == nullptr) {
        throw runtime_error("Empty");
    }
    if(head->next == nullptr) {
        T valor = head->val;
        delete head;
        head = nullptr;
        return valor;
    };

    ListNode<T>* actual = head;
    while(actual->next->next != nullptr) {
        actual = actual->next;
    }

    T valor = actual->next->val;
    delete actual->next;
    actual->next = nullptr;
    return valor;
};

template <typename T>
bool ForwardList<T>::empty(){
    return head == nullptr;
};

template <typename T>
int ForwardList<T>::size(){
    int count = 0;
    ListNode<T>* actual = head;

    while(actual != nullptr) {
        count++;
        actual = actual->next;
    };

    return count;
};

template <typename T>
void ForwardList<T>::clear() {
    while(head != nullptr) {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
};

template <typename T>
T ForwardList<T>::operator[](int pos) {
    ListNode<T>* actual = head;
    int i = 0;

    if(pos<0) {
        throw out_of_range("Numero negativo");
    }

    while(actual != nullptr && i<pos) {
        actual = actual->next;
        i++;
    }

    if(actual == nullptr) {
        throw out_of_range("Fuera de rango");
    }

    return actual->val;
};

template <typename T>
void ForwardList<T>::reverse() {
    if (head == nullptr) {
        return;
    }

    ListNode<T>* temp1 = head;

    if (head->next == nullptr) {
        return;
    }

    ListNode<T>* temp2 = head->next;
    ListNode<T>* temp3 = temp2->next;

    temp1->next = nullptr;

    while(temp3) {
        temp2->next = temp1;
        temp1 = temp2;
        temp2 = temp3;
        temp3 = temp3->next;
    }

    temp2->next = temp1;
    head = temp2;
};

template <typename T>
void ForwardList<T>::sort() {
    if (head == nullptr || head->next == nullptr) {
        return;
    };

    bool sorted;
    do {
        sorted = false;
        ListNode<T>* actual = head;
        while(actual->next != nullptr) {
            if(actual->val > actual->next->val) {
                T temp = actual->val;
                actual->val = actual->next->val;
                actual->next->val = temp;
                sorted = true;
            }
            actual = actual->next;
        }
    } while(sorted);
};




int main() {

    //Pruebas hechas con IA para comprrobar que todo funcione

    ForwardList<int> lista;

    cout << "== Probando empty() ==" << endl;
    cout << "Lista vacia? " << lista.empty() << endl; // 1 (true)

    cout << "\n== Probando push_front() y push_back() ==" << endl;
    lista.push_front(10);   // lista: 10
    lista.push_back(30);    // lista: 10 -> 30
    lista.push_front(5);    // lista: 5 -> 10 -> 30
    lista.push_back(40);    // lista: 5 -> 10 -> 30 -> 40
    cout << "Size: " << lista.size() << endl; // 4

    cout << "\n== Probando front() y back() ==" << endl;
    cout << "Front: " << lista.front() << endl; // 5
    cout << "Back: " << lista.back() << endl;   // 40

    cout << "\n== Probando operator[] ==" << endl;
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << " "; // 5 10 30 40
    }
    cout << endl;

    cout << "\n== Probando pop_front() ==" << endl;
    cout << "Eliminado front: " << lista.pop_front() << endl; // 5
    cout << "Nuevo front: " << lista.front() << endl;         // 10

    cout << "\n== Probando pop_back() ==" << endl;
    cout << "Eliminado back: " << lista.pop_back() << endl; // 40
    cout << "Nuevo back: " << lista.back() << endl;         // 30

    cout << "\n== Lista actual ==" << endl;
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << " "; // 10 30
    }
    cout << endl;

    cout << "\n== Probando reverse() ==" << endl;
    lista.reverse(); // ahora: 30 -> 10
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << " "; // 30 10
    }
    cout << endl;

    cout << "\n== Probando sort() ==" << endl;
    lista.push_back(20); // ahora: 30 -> 10 -> 20
    lista.push_back(25); // ahora: 30 -> 10 -> 20 -> 25
    lista.sort();        // ordena: 10 -> 20 -> 25 -> 30
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << " "; // 10 20 25 30
    }
    cout << endl;

    cout << "\n== Probando clear() ==" << endl;
    lista.clear();
    cout << "Size despues de clear: " << lista.size() << endl; // 0
    cout << "Lista vacia? " << lista.empty() << endl;          // 1 (true)

    return 0;

    //Pruebas hechas con IA para comprrobar que todo funcione
}












