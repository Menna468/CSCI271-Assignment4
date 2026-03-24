/*************************************************************************
* Programming Assignment 4 for CSCI 271-001 Spring 2026
*
* Author: William Klement (REPLACE THIS WITH YOUR OWN NAME)
* OS: Ubuntu Debian Linux 21.1
* Compiler: g++
* Date: March 9, 2026
*
* Purpose
* This program implements the class Lists as linked lists of generic nodes 
* The task is to implement the missing methods. 
* Please see corresponding assignemnt questions
*************************************************************************/

#include<iostream>
#include <ctime>

using namespace std;

// Global memory management counts to track allocations/deallocations
int AN = 0;
int DN = 0;

// A Generic Node Class
template <typename T> class Node{
  private:
    T element;
    Node <T>* next;

    // Allow the friend class List to access private members
    template <typename U> friend class List;

  public:
    Node(){
      this->next = NULL;
      AN += 1;  // keep track of allocations
    }

    ~Node(){
      // call destructors for the rest of the list
      if (this->next != NULL) {
        delete this->next;
        this->next = NULL;
      }

      // DO NOT REMOVE THE NEXT LINE: keep at end of your destructor method!!
      DN += 1;  // keep track of deallocations
    }
};

template <typename T> class List{
    private:
        Node<T>* head;
    public:
      // create an empty list
      List(){
        this->head = NULL;
      AN += 1;  // keep track of allocations
      }
      
      // destroy the list by destroying the nodes
      ~List(){

        if (this->head != NULL) {
          delete this->head;
          this->head = NULL;
        }

        DN += 1;  // keep track of deallocations
      }

      // check if the list is empty
      //   In this case, an empty list has a size of 0
      bool isEmpty(){
        return (this->size() == 0);
      }

      // addLast(item) adds an element item of type T at the end of the list
      void addLast(T item){
        Node<T>* newNode = new Node<T>;
        newNode->element = item;
        newNode->next = NULL;

        if (this->head == NULL) {
          this->head = newNode;
        }
        else {
          Node<T>* temp = this->head;
          while (temp->next != NULL) {
            temp = temp->next;
          }

          temp->next = newNode;
        }

        cout<<"new node added at back!"<<endl; // your method MUST use this!

      }

      // addFront(item) creates and adds a new element node 
      // containing item at the front of the list
      void addFront(T item){
        Node<T>* newNode = new Node<T>;
        newNode->element = item;
        newNode->next = this->head;
        this->head = newNode;

        cout<<"new node added at front !"<<endl; // your method MUST use this!

      }

      // addAt(index, item) creates and adds a new element node containing 
      // the elemnet item at the position speficied by indes in the list
      void addAt(int index, T item){

        // check for a valid index
        if(index > this->size() || index < 0){
          cout<<"index out of bound !"<<endl;
        }
        else {
          // create a new node with item in it
          Node<T>* pNode = new Node<T>;
          pNode->element = item;

          // Link the new node in the position indicated by index
          // start at the head of the list
          int count = 0;
          Node<T>* temp = this->head;

          // find the node before index position 
          while(temp != NULL && count < index-1){
            count++;
            temp = temp->next;
          }.<
 
          // if insertions is to happen after the first node
          if(index > 0){
            pNode->next = temp->next;
            temp->next = pNode;
          }
          else if(index==0){  // in the first position
              pNode->next = this->head;
              this->head = pNode;
          }
          cout<<"new node added at index "<<index<<" !"<<endl;
        }
      }
    
      /*
      Runtime Complexity:
      Best Case = Omega(1)
      Average Case = Theta(n)
      Worst Case = O(n)
      */
      // size() returns the number of elements in the list
      int size(){
        int len = 0;
 
        // start at the head of the list
        Node<T>* temp = this->head;

        // count the nodes all the way to NULL
        while(temp != NULL){
          len++;
          temp = temp->next;
        }
        return len;
      }

      // displayALL() prints the size and content of the list
      void displayAll(){
        cout<<"____________List of "<<this->size()<<" items________________"<<endl;

        if(this->isEmpty()){
          cout<<"The list is empty ...! "<<endl;
        }
        else{ 
          // start at the head
          Node<T>* temp = this->head;

          // print all the nodes one by one
          cout<<"[ ";
          while(temp != NULL){
            cout<<temp->element;
            temp = temp->next;
            if(temp == NULL)
              cout<<"] "<<endl;
            else
              cout<<" , ";
          }
        }
        cout<<endl;
      }
    
      // removeLast() deletes the last element and its node in the list
      void removeLast(){
        if (this->isEmpty()) {
          cout << "The list is empty!" << endl;
          return;
        }

        if (this->head->next == NULL) {
          delete this->head;
          this->head = NULL;
        }

        else {
          Node<T>* temp = this->head;
          while (temp->next->next != NULL) {
            temp = temp->next;
          }

          delete temp->next;
          temp->next = NULL;
        }

        cout<<"last item removed"<<endl; // your method MUST use this!

      }

      // removeAt(index) deletes the element and its node found at 
      // position index in the list
      void removeAt(int index){

        // check the empty list
        if(this->isEmpty()){
          cout<<"The list is empty !"<<endl;
        }
        else if(index >= this->size() || index < 0){ // verify index is valid
          cout<<"index out of bound !"<<endl;
        }
        else if(index == 0){ // remove first node
          this->removeFront();
          cout<<"item removed at index "<<index<<endl;
        }
        else{ // remove other than the first node
          int count = 0;
          Node<T>* temp = this->head; // start at the first node

          // search for the node at position index
          while(count < index - 1){ 
            count++;
            temp = temp->next;
          }
          
          Node<T>* pNode = temp->next; // hold on to that node temporarily 
          temp->next = pNode->next;    // relink around the removed node
          pNode->next = NULL;          // disconnect that node form the list
          pNode->~Node();              // destroy the node
          cout<<"item removed at index "<<index<<endl;
        }
      }

      // removeFront() deletes the last element and its node in the list
      void removeFront(){
        if (this->isEmpty()) {
          cout << "The list is empty!" << endl;
          return;
        }

        Node<T>* temp =this->head;
        this->head = this->head->next;
        temp->next = NULL;
        delete temp;

        cout<<"front item removed"<<endl; // your method MUST use this!

      }

      // getAt(int index) returns the element found at position index in the list
      T getAt(int index){
        T res = -9999;        // initialize the results to invalid element

        if (this->isEmpty()) {
          cout << "linked list is empty!" << endl;
        }

        if (index < 0 || index >= this->size()) {
          cout << "index of bound!" << endl;
          return res;
        }

        Node<T>* temp = this->head;
        int count = 0;

        while (temp != NULL) {
          if (count == index) {
            res = temp->element;
            break;
          }             
          temp = temp->next;
          count++;
        }

        return res;  // return the results -- YOU MUST USE THIS!!!!
      }     
};


// ************* DO NOT MODIFY THE CODE BELOW THIS POINT !!!! *************
int main(){
    List<int> list;
    int ch, item, index;
    bool quit = false;
    do{
        // PLEASE DO NOT REMOVE THE NEXT LINE -- ignore it!
        // if you have to know, this is used for measuring CPU start time
        std::clock_t c_start = std::clock();

        // display the menu to the user
        cout<<"____________Main Menu_____________________"<<endl;
        cout<<"select option :"<<endl;
        cout<<"1: insert back"<<endl;
        cout<<"2: insert front"<<endl;
        cout<<"3: insert at index"<<endl;
        cout<<"4: display items"<<endl;
        cout<<"5: get item at index"<<endl;
        cout<<"6: delete back"<<endl;
        cout<<"7: delete front"<<endl;
        cout<<"8: delete at index"<<endl;
        cout<<"9: exit"<<endl;
        cin>>ch;

        // execute user's choice as a switch statement
        switch (ch)
        {
        case 1:
            cout<<"enter item to insert:"<<endl;
            cin>>item;
            c_start = std::clock(); // start the CPU clock -- Please this!
            list.addLast(item);
            break;
        case 2:
            cout<<"enter item to insert:"<<endl;
            cin>>item;
            list.addFront(item);
            break;
        case 3:
            cout<<"enter item to insert:"<<endl;
            cin>>item;
            cout<<"enter index:"<<endl;
            cin>>index;
            list.addAt(index, item);
            break;
        case 4:
            list.displayAll();
            break;
        case 5:
            cout<<"enter index:"<<endl;
            cin>>index;
            cout<<"item at index "<<index<<"is: "<<list.getAt(index)<<endl;
            break;
        case 6:
            list.removeLast();
            break;
        case 7:
            list.removeFront();
            break;
        case 8:
            cout<<"enter index:"<<endl;
            cin>>index;
            list.removeAt(index);
            break;
        case 9:
            quit = true;
            break;
        default:
            cout<<"invalid selection"<<endl;
            break;
        }
        std::clock_t c_end = std::clock();
        long time_elapsed_ms = 100000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
        std::cout << "CPU time used: " << time_elapsed_ms << " ms"<<endl;
    }while(!quit);

    list.~List(); // Clean up and destroy the list

    cout<<".........................................."<<endl;
    if(AN-DN != 0) cout<<"********** MEMORY ALLOCATION ERROR ********** !!!!!!"<<endl;
    else cout<<"........   CONGRATULATIONS on memory well managed! .... :^) !!!!"<<endl;
    cout<<"Allocation Calls: "<<AN<<endl;
    cout<<"DeAllocation Calls: "<<DN<<endl;
    return 0;
}



