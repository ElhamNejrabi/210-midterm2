#include <iostream>
#include <string>
#include <fstream>
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

    bool isEmpty() { return head == nullptr; }

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
        if (!head) return;
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else head = tail = nullptr;
        delete temp;
    }

    void delete_random() {
        if (!head) return;
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        if (count == 0) return;
        int pos = rand() % count;
        temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;
        if (temp == head)
            pop_front();
        else if (temp == tail)
            pop_back();
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }

    string get_front() { return head ? head->data : ""; }
    string get_back() { return tail ? tail->data : ""; }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t" << current->data << endl;
            current = current->next;
        }
    }
};

int main() {
    srand(time(0));

    DoublyLinkedList line;
    string names[100];
    ifstream infile("names.txt");
    int nameCount = 0;

    while (getline(infile, names[nameCount]) && nameCount < 100)
        nameCount++;

    if (nameCount == 0) {
        cout << "Error: could not read any names from names.txt" << endl;
        return 1;
    }

    cout << "Store opens:\n";
    for (int i = 0; i < 5; ++i) {
        string newName = names[rand() % nameCount];
        cout << "\t" << newName << " joins the line" << endl;
        line.push_back(newName);
    }
    cout << "Resulting line:\n";
    line.print();

    for (int minute = 2; minute <= 20; ++minute) {
        cout << "Time step #" << minute << ":\n";

        int prob;

       
        prob = rand() % 100 + 1;
        if (prob <= 40 && !line.isEmpty()) {
            cout << "\t" << line.get_front() << " is served" << endl;
            line.pop_front();
        }

        
        prob = rand() % 100 + 1;
        if (prob <= 60) {
            string newName = names[rand() % nameCount];
            cout << "\t" << newName << " joins the line" << endl;
            line.push_back(newName);
        }

        
        prob = rand() % 100 + 1;
        if (prob <= 20 && !line.isEmpty()) {
            cout << "\t" << line.get_back() << " (at the rear) left the line" << endl;
            line.pop_back();
        }

        
        prob = rand() % 100 + 1;
        if (prob <= 10 && !line.isEmpty()) {
            cout << "\tA random customer left the line" << endl;
            line.delete_random();
        }

        
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            string vipName = names[rand() % nameCount];
            cout << "\t" << vipName << " (VIP) joins the front of the line" << endl;
            line.push_front(vipName);
        }

        cout << "Resulting line:\n";
        line.print();
    }

    return 0;
}
