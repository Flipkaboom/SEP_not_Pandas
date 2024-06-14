#include <iostream>
using namespace std;

const int QUEUE_SIZE = 10;
int queue[QUEUE_SIZE];
int front = 0;
int rear = 0;
int queueCount = 0;  // Renamed 'count' to 'queueCount' to avoid potential conflicts

void Enqueue(int x) {
    if (queueCount == QUEUE_SIZE) {
        cout << "\nOverflow";
    } else {
        queue[rear] = x;
        rear = (rear + 1) % QUEUE_SIZE;
        queueCount++;
    }
}

void Dequeue() {
    if (queueCount == 0) {
        cout << "\nUnderflow";
    } else {
        cout << "\n" << queue[front] << " deleted";
        front = (front + 1) % QUEUE_SIZE;
        queueCount--;
    }
}

void show() {
    if (queueCount == 0) {
        cout << "\nQueue is empty";
    } else {
        for (int i = 0; i < queueCount; i++) {
            cout << queue[(i + front) % QUEUE_SIZE] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int ch, x;
    do {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Print";
        cout << "\nEnter Your Choice (0 to exit): ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "\nInsert : ";
                cin >> x;
                Enqueue(x);
                break;
            case 2:
                Dequeue();
                break;
            case 3:
                show();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (ch != 0);

    return 0;
}
