// Purpose.  State design pattern lab
// 
// Problem.  A large monolithic case  drives the application.  As
// the program evolves, this case statemen may have to be duplicated in
// multiple places.  We want to migrate to an OO design, but we need to be
// careful not to encapsulate multiple distinct "behaviors" in a single
// object.
// 
// FSM:  Message ==> on    off   ack
//       State A     A     B     C
//       State B           A     C
//       State C                 B
// 
// Assignment.
// o Define an FSM context (wrapper, handle, interface) class
// o FSM declares a private data member of type FSMstate* to remember its
//   "current state"
// o FSM defines the member functions on(), off(), and ack().  Each of these
//   functions delegates to the contained object by calling its member func-
//   tion of the same name, and passing the FSM's "this" pointer. [GOF, p310,
//   bottom]
// o FSM declares class FSMstate as friend (because FSMstate will be setting
//   the "current state" member)
// o Define an FSMstate base class
// o FSMstate defines a default implementation for all FSM messages (on, off,
//   ask).  The implementation of each will look like -
//      virtual void on( FSM* ) { cout << "undefined combo" << endl; }
// o FSMstate defines a protected member function -
//      void changeState( FSM*, FSMstate* )
//   This is used by the derived state classes to set the "current state"
//   member of the FSM.  This "indirection" is necessary because "friendship"
//   is not inherited by derived classes. [GOF, p311]
// o Declare states A, B, and C as derived classes of FSMstate
// o Design states A, B, and C as Singletons
// o Each of these classes override only those messages that they respond to
// o The bodies of the on(), off(), and ack() methods are simply the bodies
//   of the "case" clauses below, except that the state machine's state is
//   changed by calling the base class's changeState() method and passing the
//   "instance" of the desired FSMstate derived class.  [Note: state
//   transitions are defined in each individual state object.  This results
//   in coupling between the derived classes, but it also provides for
//   decentralization of intelligence or control.]
// o FSM's constructor initializes its "current state" member to state "B"
// o The body of main() reduces to "FSM fsm;" plus a minimal driver loop

#include <iostream.h>

enum State   { A, B, C };
enum Message { on, off, ack };
State        currentState;
Message      messageArray[10] = { on,off,off,ack,ack,ack,ack,on,off,off };

void main( void ) {
   currentState = B;
   for (int index=0; index < 10; index++) {
      if (currentState == A) {
         if (messageArray[index] == on) {
            cout << "A, on ==> A" << endl;
            currentState = A;
         } else if (messageArray[index] == off) {
            cout << "A, off ==> B" << endl;
            currentState = B;
         } else if (messageArray[index] == ack) {
            cout << "A, ack ==> C" << endl;
            currentState = C;
         }
      } else if (currentState == B) {
         if (messageArray[index] == on) {
            cout << "undefined combo" << endl;
         } else if (messageArray[index] == off) {
            cout << "B, off ==> A" << endl;
            currentState = A;
         } else if (messageArray[index] == ack) {
            cout << "B, ack ==> C" << endl;
            currentState = C;
         }
      } else if (currentState == C) {
         if (messageArray[index] == on) {
            cout << "undefined combo" << endl;
         } else if (messageArray[index] == off) {
            cout << "undefined combo" << endl;
         } else if (messageArray[index] == ack) {
            cout << "C, ack ==> B" << endl;
            currentState = B;
         }
      }
   }
}

// undefined combo
// B, off ==> A
// A, off ==> B
// B, ack ==> C
// C, ack ==> B
// B, ack ==> C
// C, ack ==> B
// undefined combo
// B, off ==> A
// A, off ==> B
