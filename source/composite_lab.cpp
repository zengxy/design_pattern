// Purpose.  Composite design pattern lab.
//
// Problem.  Approach is now more space efficient, but casting and type
// checking are required to coerce the compiler.  The abstraction needs to
// be improved so that Primitive and Composite can be treated
// transparently in a sibling context, while still maintaining their
// specialization.
//
// Assignment.
// o Create a class Component to serve as a base class.  Primitive and
//   Composite should inherit from Component.
// o Move anything that is (or needs to be) common in both Primitive and
//   Composite up into Component.
// o Currently class Composite is coupled to itself (the argument to add() and
//   the children private data member).  It needs to be coupled only to its
//   abstract base class.
// o You can now remove: NodeType, reportType(), the casting in main() and
//   Composite::traverse(), and the "type checking" in Composite::traverse()

#include <iostream.h>
enum NodeType { LEAF, INTERIOR };

class Primitive {
public:
   Primitive( int val ) : value(val), type(LEAF)  { }
   NodeType reportType()                          { return type; }
   void     traverse()                            { cout << value << " "; }
private:
   int       value;
   NodeType  type;
};

class Composite {
public:
   Composite( int val ) : value(val), type(INTERIOR)  { total = 0; }
   NodeType reportType()                              { return type; }
   void     add( Composite* c )                       { children[total++] = c; }
   void traverse() {
      cout << value << " ";
      for (int i=0; i < total; i++)
         if (children[i]->reportType() == LEAF)
            ((Primitive*) children[i])->traverse();
         else   
            children[i]->traverse();
   }
private:
   int         value;
   NodeType    type;
   int         total;
   Composite*  children[99];
};

void main( void ) {
   Composite  first(1), second(2), third(3);

   first.add( &second );
   first.add( &third );
   first.add( (Composite*) new Primitive(4) );
   second.add( (Composite*) new Primitive(5) );
   second.add( (Composite*) new Primitive(6) );
   third.add( (Composite*) new Primitive(7) );
   first.traverse();
   cout << endl;
}

// 1 2 5 6 3 7 4
