/***
* Vik Dhillon
* vsdhillo
* 2025 Winter CSE101 PA5
* List.cpp
* Program to write the List ADT
***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include <unordered_set>


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty Queue
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of Q into this Queue
   Node* N = L.frontDummy->next;
   while(N!= L.backDummy){
      insertBefore(N->data);
      N = N->next;
   }

   moveFront();
   for (int i = 0; i < L.pos_cursor; i++) {
      moveNext();
   }
   // std::cout << "***called copy constructor: " << this->to_string() << std::endl;
}

// Destructor
List::~List(){
   moveFront();
   while (num_elements > 0) {
    eraseAfter();
   }

   delete frontDummy;
   delete backDummy;
   // std::cout << "***called destructor" << std::endl;
}


// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if Queue is empty, otherwise returns false.
int List::length() const{
   return num_elements;
}

// getFront()
// Returns the value at the front of Queue.
// Pre: !isEmpty()
ListElement List::front() const{
   if(num_elements==0 ){
      throw std::length_error("List: front(): empty List");
   }
   return(frontDummy->next->data);
}

ListElement List::back() const{
    if( num_elements==0 ){
       throw std::length_error("List: back(): empty List");
    }
    return(backDummy->prev->data);
 }

// getLength()
// Returns the length of Queue.
int List::position() const{
   return (pos_cursor);
}

ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: peekNext(): cursor is at back");
    }
    return (afterCursor->data);
}

ListElement List::peekPrev() const {
    if (pos_cursor <= 0) {
        throw std::range_error("List: peekPrev(): cursor is at front");
    }
    return (beforeCursor->data);
}


// Manipulation procedures ----------------------------------------------------

void List::clear() {
    for (Node * N = frontDummy->next, *temp; N!= backDummy; N = temp) {
        temp = N->next;
        delete N;
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: moveNext(): cursor can't move forward");
    }
    beforeCursor = afterCursor;
    afterCursor=afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: movePrev(): cursor can't move backward");
    }
    afterCursor = beforeCursor;
    beforeCursor=beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;

    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
    //pos_cursor++;
}

void List::insertBefore(ListElement x) {
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;

    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: setAfter(): cannot set after cursor");
    }

    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) {
        throw std::range_error("List: setBefore(): cannot set before cursor");
    }

    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): cannot erase after cursor");
    }
    //std::cout << "Pos cursor: " << pos_cursor << std::endl;
    Node *temp = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
        
    delete temp;

    num_elements--;

}

void List::eraseBefore() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: eraseBefore(): cannot erase before cursor");
    }
    
    Node *temp = beforeCursor;
    //std::cout << "beforeCursor prev: " <<beforeCursor->prev->data << std::endl;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    //std::cout << "afterCursor prev: " <<afterCursor->data << std::endl;
    afterCursor->prev = beforeCursor;
    delete temp;
    
    num_elements--;
    pos_cursor--;

}

std::string List::to_string() const{
    std::string result = "";
    if (num_elements == 0) {
        return result;
    }
    Node *N = nullptr;
    for(N=frontDummy->next; N!=backDummy;N=N->next) {
        result += std::to_string(N->data) + " ";
    }
    return result;
}

int List::findNext(ListElement x) {
    for(Node *N = afterCursor;N!=backDummy;N=N->next) {
        pos_cursor++;
        if (N->data == x) {
            beforeCursor = N;
            afterCursor = N->next;
            return pos_cursor;
        }
    }
    pos_cursor = num_elements;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    return -1;
}

int List::findPrev(ListElement x) {
    for(Node *N = beforeCursor;N!=frontDummy;N=N->prev) {
        pos_cursor--;
        if (N->data == x) {
            beforeCursor = N->prev;
            afterCursor = N;
            return pos_cursor;
        }
    }
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    return -1;
}

void List::cleanup() {
   std::unordered_set<ListElement> set;
   int i = 0;
   int deleteCounter = 0;
   Node *N = frontDummy->next;
   while (N!=backDummy) {
      if (set.find(N->data) != set.end()) {
         num_elements--;
         if (N == beforeCursor) {
            Node *temp = N;
            beforeCursor = temp->prev;
            beforeCursor->next = afterCursor;
            afterCursor->prev = beforeCursor;
            N = beforeCursor->next;
            delete temp;
         }
         else if (N == afterCursor) {
            Node *t = N;
            afterCursor = t->next;
            afterCursor->prev = beforeCursor;
            beforeCursor->next = afterCursor;
            N = afterCursor;
            delete t;
         }
         else {
            Node *te = N;
            N->prev->next = N->next;
            N->next->prev = N->prev;
            N = N->next;
            delete te;
         }

         if (i < pos_cursor) {
            deleteCounter++;
          }
      }

      else {
        set.insert(N->data);
        N = N->next;
      }

      i++;
   }

   pos_cursor -= deleteCounter;

}

List List::concat(const List& L) const {
    List final;
    for (Node *N = frontDummy->next; N!=backDummy; N=N->next) {
        final.insertBefore(N->data);
    }

    for (Node *Q = L.frontDummy->next; Q!=L.backDummy; Q=Q->next) {
        final.insertBefore(Q->data);
    }

    final.moveFront();
    return final;
}

bool List::equals(const List& R) const {
    if (num_elements != R.num_elements) {
        return false;
    }
    bool isEqual = true;
    Node *A = frontDummy->next;
    Node *B = R.frontDummy->next;

    while (A!= backDummy && B!= R.backDummy) {
        if (A->data != B->data) {
            isEqual = false;
            break;
        }
        else {
            A = A->next;
            B = B->next;
        }
    }
    return isEqual;

}

std::ostream& operator<<( std::ostream& stream, const List& L ) {
    stream << L.to_string();
    return stream;
}

bool operator==( const List& A, const List& B ) {
    if (A.equals(B)) {
        return true;
    }
    else {
        return false;
    }
}

List& List::operator=(const List& L) {
    if (this != &L) {  
        this->clear();  
  
        moveFront();  
        for (Node *N = L.frontDummy->next; N!= L.backDummy; N = N->next) {
            insertAfter(N->data);
            moveNext();
        }

        moveFront();
        for (int i = 0; i < L.pos_cursor; i++) {
            moveNext();
        }
    }
    return *this;
}

