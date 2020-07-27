#include "Exam.h"
#include "LNode.h"
#include <iostream>

using namespace std;

void populate(Node **arr, int n) {
    // your code here

    for (int i=0; i<n; i++){
      arr[i] = new LNode();
    }
}

void lookPrev(Node **arr, int n) {
    // your code here
    for (int i=n-1; i>0;i--){
      arr[i]->setLookingAt(arr[i-1]);
    }
    arr[0]->setLookingAt(NULL);
}

void display(Node **arr, int n) {
    Node *x;
    for(int i=0; i<n; i++) {
        x = arr[i]->getLookingAt();
        if (x)
            cout << "Node " << arr[i] << " is looking at " << x << "." << endl;
        else
            cout << "Node " << arr[i] << " is looking at NULL." << endl;
    }
}
