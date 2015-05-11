// Purpose.  Chain of Responsibility design pattern lab
// 
// Problem.  Four Slot objects are being used, and the client has to know
// about and interact with all of them.  It would be preferable to decouple
// the client from its many servers by encapsulating all the Slot objects
// in a single pipeline, or chain, abstraction.  The advantages are:
// "request handling" algorithms are hidden in the pipeline abstraction, and
// client complexity is reduced because it can now "launch and leave" all
// requests with the head of the pipeline and the pipeline "divides and
// conquers" the request across its collection of processing elements.
// 
// Assignment.
// o Add a Slot* data member to Slot that will point to each Slot's successor
//   in the chain
// o Modify the constructors for Slot, Quarter, Dime, Nickel, and Penny to
//   accept a Slot* and initialize the Slot* data member (use an "=0" default
//   argument)
// o Change accept() to delegate to the successor if the conditional expression
//   does not succeed (accept() can now have a void return type)
// o Add a report() member function to the Slots hierarchy that encapsulates
//   the functionality of the final four cout's in main().
// o Encapsulate the slots array set-up in a free function.  Create the "chain"
//   in this function and return it to main().
// o Change main() to eliminate all knowledge of, or interaction with, the
//   number and type of Slot objects.

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

class Slot {
public:
   Slot( int val ) {
      value_ = val;
      count_ = 0; }
   int accept( int coin ) {
      if (coin == value_) {
         count_++;
         return 1; }
      return 0; }
   int getCount() {
      return count_; }
private:
   int  value_;
   int  count_;
};

class Quarter : public Slot {
public:
   Quarter() : Slot( 25 ) { }
};

class Dime : public Slot {
public:
   Dime() : Slot( 10 ) { }
};

class Nickel : public Slot {
public:
   Nickel() : Slot( 5 ) { }
};

class Penny : public Slot {
public:
   Penny() : Slot( 1 ) { }
};

int pickCoin()
{
   static int choices[4] = { 1, 5, 10, 25 };
   return choices[rand() % 4];
}

void main( void )
{
   Slot*    slots[4];
   slots[0] = new Quarter;
   slots[1] = new Dime;
   slots[2] = new Nickel;
   slots[3] = new Penny;
   int      i, coin, total;
   time_t   t;
   srand((unsigned) time(&t));

   for (i=0, total=0; i < 10; i++)
   {
      coin = pickCoin();
      cout << coin << " ";
      total += coin;
      for (int j=0; j < 4; j++)
         if (slots[j]->accept( coin )) break;
   }
   cout << "\ntotal deposited is $" << total/100 << "."
      << (total%100 < 10 ? "0" : "") << total%100 << endl;
   cout << "quarters - " << slots[0]->getCount() << endl;
   cout << "dimes    - " << slots[1]->getCount() << endl;
   cout << "nickels  - " << slots[2]->getCount() << endl;
   cout << "pennies  - " << slots[3]->getCount() << endl;
}

// 10 5 25 5 1 25 5 25 1 25 
// total deposited is $1.27
// quarters - 4
// dimes    - 1
// nickels  - 3
// pennies  - 2
// 
// 25 25 10 5 1 5 10 5 1 5 
// total deposited is $0.92
// quarters - 2
// dimes    - 2
// nickels  - 4
// pennies  - 2
// 
// 5 10 25 10 25 1 25 10 1 25 
// total deposited is $1.37
// quarters - 4
// dimes    - 3
// nickels  - 1
// pennies  - 2
