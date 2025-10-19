#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;       
        Node* prev;
        Node* next;

        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else
            head = tail = nullptr;
        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    srand(time(0)); 
    DoublyLinkedList line; 
    ifstream infile("names.txt");

    if (!infile) {
        cout << "Error: could not open names.txt" << endl;
        return 1;
    }

   
    vector<string> names;
    string name;
    while (getline(infile, name)) {
        names.push_back(name);
    }

    cout << "Store opens:\n";

    
    for (int i = 0; i < 5; i++) {
        string randomName = names[rand() % names.size()];
        line.push_back(randomName);
        cout << "    " << randomName << " joins the line" << endl;
    }

    cout << "Resulting line:\n    ";
    line.print();

    return 0;
}


