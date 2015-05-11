// Purpose.  Adapter design pattern lab
// 
// Problem.  Simulated here is a "stack machine", or a non-OO
// implementation of a Stack class.  We would like to reuse this "legacy"
// asset as the basis for a new Queue class, but there is an "impedance
// mismatch" between the old and the new.
// 
// Assignment.
// o The class Queue should contain an "instance" of component Stack.
// o Queue needs a constructor, destructor, enque, deque, and isEmpty methods.  
//   Each of these methods will provide an adaptation from the Queue interface to the
//   Stack implementation.
// o If you map Queue's enque() to Stack's push(), then the pseudocode below
//   will give you insight into implementing Queue's deque() method.

#include <iostream.h>

struct StackStruct {
   int*  array;
   int   sp;
   int   size;
};
typedef StackStruct Stack;

static void initialize( Stack* s, int size ) {
   s->array = new int[size];
   s->size = size;
   s->sp = 0; }
static void cleanUp( Stack* s ) {
   delete s->array; }
static int isEmpty( Stack* s ) {
   return s->sp == 0 ? 1 : 0; }
static int isFull( Stack* s ) {
   return s->sp == s->size ? 1 : 0; }
static void push( Stack* s, int item ) {
   if ( ! isFull(s)) s->array[s->sp++] = item; }
static int pop( Stack* s ) {
   if (isEmpty(s)) return 0;
   else            return s->array[--s->sp]; }

class Queue {
   deque pseudocode:
      initialize a local temporary instance of Stack
      loop
         pop() the permanent stack and push() the temporary stack
      pop() the temporary stack and remember this value
      loop
         pop() the temporary stack and push() the permanent stack
      cleanUp the temporary stack
      return the remembered value
   int isFull()  { return ::isFull( &_stack );  }
};

int main() {
   Queue  queue(15);

   for (int i=0; i < 25; i++) queue.enque( i );
   while ( ! queue.isEmpty()) cout << queue.deque() << " ";
   cout << endl;
   return 1;
}

// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
