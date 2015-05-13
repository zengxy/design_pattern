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

#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

class Slot
{
public:
    Slot( int val,Slot* p=0 )
    {
        value_ = val;
        count_ = 0;
        pSuccessor=p;
    }
    void accept( int coin )
    {
        if (coin == value_)
            count_++;
        else
            pSuccessor->accept(coin);
    }
    int getCount()
    {
        return count_;
    }
    virtual void report()=0;
protected:
    int  value_;
    int  count_;
    Slot* pSuccessor;
};

class Quarter : public Slot
{
public:
    Quarter(Slot* p=0) : Slot( 25 ,p)
    {
    }
    void report()
    {
        cout << "quarters - " << count_ << endl;
    }

};

class Dime : public Slot
{
public:
    Dime(Slot* p=0) : Slot( 10,p ) { }
    void report()
    {
        cout << "dimes - " << count_ << endl;
    }
};

class Nickel : public Slot
{
public:
    Nickel(Slot* p=0) : Slot( 5 ,p) { }
    void report()
    {
        cout << "nickels - " << count_ << endl;
    }
};

class Penny : public Slot
{
public:
    Penny(Slot* p=0) : Slot( 1 ,p) { }
    void report()
    {
        cout << "pennies - " << count_ << endl;
    }
};

int pickCoin()
{
    static int choices[4] = { 1, 5, 10, 25 };
    return choices[rand() % 4];
}


Slot* arraySetup(Slot* slots[],int num)
{
    slots[0] = new Penny;
    slots[1] = new Nickel(slots[0]);
    slots[2] = new Dime(slots[1]);
    slots[3] = new Quarter(slots[2]);
}


int main()
{
    Slot*    slots[4];
    arraySetup(slots,4);

    int      i, coin, total;
    time_t   t;
    srand((unsigned) time(&t));

    for (i=0, total=0; i < 10; i++)
    {
        coin = pickCoin();
        cout << coin << " ";
        total += coin;
        slots[3]->accept(coin);
    }
    cout << "\ntotal deposited is $" << total/100 << "."
         << (total%100 < 10 ? "0" : "") << total%100 << endl;

    for(i=0; i<4; i++)
        slots[i]->report();
    return 1;
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
