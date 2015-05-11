// Purpose.  Bridge design pattern lab
// 
// Problem.  Our Stack class needs to allow the client to specify at
// run-time what implementation strategy to employ (i.e. list vs array).
// 
// Assignment.
// o Rename the current Stack class to ArrayImp
// o Create a base class called StackImp
// o StackImp is a "pure abstract base class".  It should declare 4 pure
//   virtual functions: push(), pop(), isEmpty(), and isFull()
// o Derive classes ArrayImp and ListImp from class StackImp
// o Create an interface (or wrapper, or handle) class called Stack
// o The class Stack should contain a pointer to the abstract base class
//   StackImp.
// o To initialize the StackImp pointer, Stack needs a constructor that
//   accepts one argument of type ImplementationType.  In the body, you
//   create an instance of the derived class requested.  If the client does
//   not supply an argument for the constructor, provide a default argument
//   of ArrayImplementation.
// o Don't forget to write a destructor to clean-up the StackImp pointer
// o The class Stack should have a method for anything a client might want to
//   do to a Stack object.  Each method simply forwards the client request to
//   the appropriate method in its StackImp object.
// o Un-comment the code in main() and test your results

#include <iostream.h>
enum ImplementationType { ArrayImplementation, ListImplementation };


class Stack {
public:
   Stack( int = 10 );
   ~Stack();
   void push( int val );
   int  pop();
   int  isEmpty();
   int  isFull();
private:
   int* _array;
   int  _sp;
   int  _size;
};


class Node {
public:
   Node( int val, Node* next );
   int getValue();
   Node* getNext();
private:
   int    _value; 
   Node*  _next;
};

class ListImp {
public:
    ListImp();
    ~ListImp();
    void push( int val );
    int  pop();
    int  isEmpty();
    int  isFull();
private:
    Node* _head;
};

void main ( void ) {
   Stack stack1;
   // Stack stack2( ListImplementation );

   for (int i=1; i < 16; i++) {
      stack1.push( i );
      // stack2.push( i );
   }

   cout << "Array stack: ";
   for (i=1; i < 18 ; i++)
      cout << stack1.pop() << "  ";
   cout << endl;

   // cout << "List stack:  ";
   // for (i=1; i < 18 ; i++)
   //    cout << stack2.pop() << "  ";
   // cout << endl;
}

// Array stack: 10  9  8  7  6  5  4  3  2  1  0  0  0  0  0  0  0  
// List stack:  15  14  13  12  11  10  9  8  7  6  5  4  3  2  1  0  0  


Stack::Stack( int size ) {
   _array = new int[size];
   _size = size;
   _sp = 0; }
Stack::~Stack() { delete _array; }
void Stack::push( int val ) {
   if ( ! isFull())
      _array[_sp++] = val; }
int Stack::pop() {
   if (isEmpty()) return 0;
   else return _array[--_sp]; }
int Stack::isEmpty() { return _sp == 0 ? 1 : 0; }
int Stack::isFull()  { return _sp == _size ? 1 : 0; }

Node::Node( int val, Node* next ) {
   _value = val;
   _next = next; }
int   Node::getValue() { return _value; }
Node* Node::getNext()  { return _next; }

ListImp::ListImp() { _head = NULL; }
ListImp::~ListImp() {
   Node  *current, *previous;
   current = _head;
   while (current) {
      previous = current;
      current = current->getNext();
      delete previous; }
}
void ListImp::push( int val ) {
   Node*  temp = new Node( val, _head );
   _head = temp; }
int ListImp::pop() {
   if (isEmpty()) return 0;
   Node*  temp = _head;
   int    val  = _head->getValue();
   _head = _head->getNext();
   delete temp;
   return val; }
int ListImp::isEmpty() { return _head ? 0 : 1; }
int ListImp::isFull()  { return 0; }
