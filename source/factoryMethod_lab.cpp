// Purpose.  Factory Method design pattern lab
//
// Problem.  The client code in main() is doing a good job of depending only
// on an abstract base class (FederalFraudvillian), and not getting coupled
// to any of the concrete derived classes.  But, coupling still exists where
// each individual concrete instance is created.  A "factory" abstraction
// implemented with factory methods (or "virtual constructors") would allow
// this last bit of coupling to be eliminated.  We would like to remove all
// dependencies on the President, AttorneyGeneral, and
// MinorityPartyCongressPerson classes so that their declarations (and inline
// definitions) can be moved below the client code in main().  [Note: the
// ordering of declarations and definitions demonstrates nicely the
// dependencies that exist within the code.]  We would also like to support
// "equal opportunity political satire" by abstracting a "political party"
// factory base class, and then instantiating one of two different derived
// classes: DemocratFactory or RepublicanFactory.
//
// Assignment.
// o Create a Factory base class with createPresident(), etc, factory methods
//   (pure virtual functions)
// o Create two classes derived from Factory: DemocratFactory, and
//   RepublicanFactory
// o Instantiate a factory object at the top of main() with code like -
//      #ifdef DEMOCRAT
//         Factory* factory = new DemocratFactory;
//      #else
//         Factory* factory = new RepublicanFactory;
//      #endif
// o Replace the calls to "new" in main() with calls to createPresident(), etc
// o The "new"s that were being performed in main() should now be done in the
//   Factory derived classes's factory methods
// o Add a 1-arg constructor to the classes President, AttorneyGeneral, and
//   MinorityPartyCongressPerson.  Use a "member initialization list" to map
//   the char* argument the constructor receives to the Base class's 1-arg
//   constructor.
// o The Factory derived classes will provide the value for the argument you
//   just added
// o Move as many declarations and definitions as possible below main() to
//   demonstrate the minimal coupling that remains

#include <iostream.h>
#include <string.h>

class FederalFraudvillian {
public:
   FederalFraudvillian( char* pp = "Democrat" ) { strcpy( party, pp ); }
   virtual void partyLine() = 0;
protected:
   char party[20];
};

class President : public FederalFraudvillian {
public:
   void partyLine() { cout << party << ": speak no evil" << endl; }
};

class AttorneyGeneral : public FederalFraudvillian {
public:
   void partyLine() { cout << party << ": see no evil" << endl; }
};

class MinorityPartyCongressPerson : public FederalFraudvillian {
public:
   void partyLine() { cout << party << ": hear no evil" << endl; }
};

void main( void ) {
   FederalFraudvillian*  moralMisfits[10];
   int      in, i, total = 0;

   cout << "President(1) AG(2) MPCP(3) Go(0): ";
   cin >> in;
   while (in) {
      if (in == 1)      moralMisfits[total++] = new President;
      else if (in == 2) moralMisfits[total++] = new AttorneyGeneral;
      else              moralMisfits[total++] = new MinorityPartyCongressPerson;
      cout << "President(1) AG(2) MPCP(3) Go(0): ";
      cin >> in;
   }
   for (i=0; i < total; i++) moralMisfits[i]->partyLine();
   for (i=0; i < total; i++) delete moralMisfits[i];
}

// no compiler directive -
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 2
// President(1) AG(2) MPCP(3) Go(0): 3
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 0
// Republican: speak no evil
// Republican: see no evil
// Republican: hear no evil
// Republican: speak no evil

// -DDEMOCRAT -
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 2
// President(1) AG(2) MPCP(3) Go(0): 3
// President(1) AG(2) MPCP(3) Go(0): 1
// President(1) AG(2) MPCP(3) Go(0): 0
// Democrat: speak no evil
// Democrat: see no evil
// Democrat: hear no evil
// Democrat: speak no evil
