// Purpose.  Decorator design pattern lab
// 
// Problem.  Inheritance is being used to produce lots of incremental
// customizations.  This is fine - until all the potential permutations of
// options gets out of hand.  Another limitation is the static nature of
// inheritance.  For any particular combination of options to be useable,
// the class hierarchy must explicitly implement that combination.  It would
// be much better if all the individual "options" could each be represented
// by their own class, and, the client could dynamically compose her
// peculiar list of options at run-time.
// 
// Assignment.
// o Add an abstract base class Expression with the single pure virtual
//   function evaluate().
// o Function should inherit from Expression (but otherwise remain unchanged).
// o Add a base class Decorator that inherits from Expression.
// o Add an Expression* data member to Decorator (this will be used to remember
//   the "core" object that this Decorator instance is "wrapping").
// o Decorator needs a constructor to initialize this Expression* data member.
// o Decorator's evaluate() should do nothing more than delegate to the
//   Expression* data member.
// o LowCut and HighCut should now inherit from Decorator instead of Function.
// o Eliminate MiddlePass.
// o Add an Expression* parameter to LowCut's and HighCut's constructors (this
//   is the "core" object that this "onion skin" is going to be wrapping).
// o Use a member initialization list to communicate the Expression* parameter
//   to the Decorator base class.
// o LowCut's and HighCut's evaluate() should now call base class Decorator's
//   evaluate() instead of Function's (Function is no longer serving as a base
//   class).
// o Now that LowCut and HighCut no longer have an "isa" relationship to
//   Function (they are now "embellishments" for a core object of type
//   Function), the "lc" and "hc" local variables in main() must have a
//   Function* at the "core" of their constructor arguments.  This could be
//   done with an inline dynamic allocation (new Function).
// o The MiddlePass class no longer exists.  Therefore, the "mp" local variable
//   in main() will be configured by using a layering of "decorator" objects on
//   a "core" object.

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

class Function {
public:
   Function() {
      time_t t;
      srand((unsigned) time(&t)); }
   virtual int evaluate() {
      return rand() % 30; }
};

class LowCut : virtual public Function {
public:
   LowCut( int min ) {
      minimum_ = min; }
   int evaluate() {
      int temp = Function::evaluate();
      if (temp < minimum_) return minimum_;
      return temp; }
protected:
   int  minimum_;
};

class HighCut : virtual public Function {
public:
   HighCut( int max ) {
      maximum_ = max; }
   int evaluate() {
      int temp = Function::evaluate();
      if (temp > maximum_) return maximum_;
      return temp; }
protected:
   int  maximum_;
};

class MiddlePass : public LowCut, public HighCut {
public:
   MiddlePass( int min, int max ) : LowCut(min), HighCut(max) { }
   int evaluate() {
      int temp = LowCut::evaluate();
      if (temp > maximum_) return maximum_;
      return temp; }
};

void main( void )
{
   LowCut      lc( 7 );
   HighCut     hc( 23 );
   MiddlePass  mp( 10, 20 );
   int         i;

   for (i=0; i < 25; i++) cout << lc.evaluate() << " "; cout << endl;
   for (i=0; i < 25; i++) cout << hc.evaluate() << " "; cout << endl;
   for (i=0; i < 25; i++) cout << mp.evaluate() << " "; cout << endl;
}

// 27 18 7 13 19 13 22 16 22 16 17 11 13 13 10 20 22 7 8 23 14 7 29 7 15 
// 2 22 23 15 8 16 7 18 7 10 6 21 6 19 3 23 0 20 5 13 23 3 2 6 1 
// 18 19 20 20 12 10 14 14 13 14 20 20 20 10 12 18 10 11 10 18 20 20 10 10 10 
// 
// 11 19 26 27 7 7 25 15 10 9 23 8 10 13 20 18 14 7 7 17 7 7 7 22 25 
// 11 4 6 23 22 10 15 23 22 2 12 19 19 12 13 18 6 15 6 1 13 1 10 14 23 
// 18 20 20 20 10 20 17 10 20 15 20 17 10 16 10 10 10 17 20 20 11 14 20 10 10 
// 
// 7 7 11 29 27 7 11 16 27 15 10 26 27 7 11 28 17 7 7 13 11 20 26 21 29 
// 22 23 23 23 3 13 17 13 12 0 23 23 3 11 14 23 13 4 0 23 9 22 23 14 14 
// 10 10 10 10 10 10 10 10 19 14 14 10 13 10 11 14 20 16 20 20 20 10 18 18 10 
