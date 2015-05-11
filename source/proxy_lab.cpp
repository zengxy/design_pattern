// Purpose.  Proxy design pattern lab (reference counting)
// 
// Discussion.  One of the four common situations in which the Proxy pattern is
// applicable is as a "smart reference" - a replacement for a bare pointer that
// performs additional actions when an object is referenced.  Here, that addi-
// tional action is "reference counting".  The original String class becomes
// the inner "body" class.  A "count" data member is added to the body class.
// A new outer "handle" class is created that contains a pointer to a body
// instance.  Body instances common to multiple handle instances are shared by
// simply incrementing the reference count.  As these shared references go away,
// the reference count is decremented.  When the count goes to zero, the body
// instance is freed.  This mechanism allows the "reference counted class" to
// perform simple-minded garbage collection on itself.
// 
// Assignment.
// o Change the class String to an inner body StringRep.
// o Add a count_ private data member to StringRep.  Initialize count_ to 1 in
//   the default ctor and the 1-arg ctor.
// o Create a new outer handle class String. Make String a friend of StringRep.
// o String has one private data member - a pointer to a StringRep (rep_).
// o The String default ctor initializes rep_ with 'new StringRep("")'.
// o The String 1-arg ctor initializes rep_ with 'new StringRep(arg)'.
// o The String copy ctor initializes rep_ with the rep_ of the initializing
//   String.  It also increments the count_ of that rep_.
// o The String dtor decrements the count_ of rep_ and deletes rep_ if count_
//   is 0.
// o The String operator=(): increments the count_ of the "rhs" rep_,
//   decrements the count_ of its own rep_ and deletes rep_ if count_ is 0,
//   assigns the "rhs" rep_ to its own rep_, and returns *this.
// o Add cout statements to String to generate the target output.
// o Make the operator<<() function a friend of both StringRep and String.
//   Modify it as necessary.

#include <iostream.h>
#include <string.h>

class String {
public:
   friend ostream& operator << ( ostream&, String& );
   String() {
      cout << "   String ctor (def):" << endl;
      str_ = NULL;
   }
   String( const char* in ) {
      cout << "   String ctor: " << in << '.' << endl;
      str_ = new char[strlen(in) + 1];
      strcpy( str_, in );
   }
   String( String& str ) {
      cout << "   String ctor (copy): " << str.str_ << '.' << endl;
      str_ = new char[strlen(str.str_) + 1];
      strcpy( str_, str.str_ );
   }
   ~String() {
      cout << "   String dtor: " << str_ << '.' << endl;
      delete str_;
   }
   String& operator= ( String& rhs ) {
      if (this == &rhs)  return *this;
      delete str_;
      str_ = new char[strlen(rhs.str_) + 1];
      strcpy( str_, rhs.str_ );
      return *this;
   }
private:
   char*  str_;
};

ostream& operator << ( ostream& os, String& str ) { return os << str.str_; }

void main( void ) {
   String  a( "hello" );
   String  b = "world";
   String  c( a );
   String  d = a;
   String  e;
   a = b;
   e = b;
   cout << "a is " << a << '.' << endl;
   cout << "b is " << b << '.' << endl;
   cout << "c is " << c << '.' << endl;
   cout << "d is " << d << '.' << endl;
   cout << "e is " << e << '.' << endl;
}

/****** Current output ******/
//    String ctor: hello.
//    String ctor: world.
//    String ctor (copy): hello.
//    String ctor (copy): hello.
//    String ctor (def):
// a is world.
// b is world.
// c is hello.
// d is hello.
// e is world.
//    String dtor: world.
//    String dtor: hello.
//    String dtor: hello.
//    String dtor: world.
//    String dtor: world.

/****** Target output ******/
//    StringRep ctor: hello.
// String ctor: hello.
//    StringRep ctor: world.
// String ctor: world.
// String ctor (copy): hello.
// String ctor (copy): hello.
//    StringRep ctor: .
// String ctor (def):
//    StringRep dtor: .
// a is world.
// b is world.
// c is hello.
// d is hello.
// e is world.
// String dtor: world, before decrement, count is 3
// String dtor: hello, before decrement, count is 2
// String dtor: hello, before decrement, count is 1
//    StringRep dtor: hello.
// String dtor: world, before decrement, count is 2
// String dtor: world, before decrement, count is 1
//    StringRep dtor: world.
