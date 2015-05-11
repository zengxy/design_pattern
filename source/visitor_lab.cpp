// Purpose.  Visitor design pattern lab
// 
// Problem.  "Open for extension, closed for modification" is a dominant
// principle of object-oriented design.  The Composite design pattern is an
// excellent strategy for designing recursively, or hierarchically, related
// collections of objects.  Once the Composite hierarchy is produced, adding
// new methods (that operate on the hierarchy) requires either: violating the
// "open-closed" principle, or, writing client code that has to do "type
// checking" and "type casting" in order to "recover lost type information".
// This latter approach is modeled below in the cat() and wc() methods of
// class Client.  The Visitor pattern specifies that a single access method
// be added to the Composite hierarchy.  Once this is done, many new methods
// can be added in the future, the "open-closed" principle can be enforced,
// and, the ugly code for "recovering lost type information" can be avoided.
// 
// Assignment.
// o Define a Visitor base class with 3 pure virtual member functions:
//      void visit( Primitive* ) = 0;
//      void visit( Link* )      = 0;
//      void visit( Composite* ) = 0;
// o Define 2 derived classes of Visitor (CatVisitor and WcVisitor) that
//   encapsulate the ugly code in class Client.  The implementation of each of
//   the overloaded visit() methods will be the body of one of the conditional
//   clauses of the existing cat() and wc() methods.
// o Add a pure virtual member function to Component:
//      void accept( Visitor& ) = 0;
// o Define accept() in all 3 Component derived classes as:
//      void accept( Visitor& v ) { v.visit( this ); }
// o Create CatVisitor and WcVisitor objects in main().
// o The body of main()'s "for" loop will become:
//      array[i]->accept( aCatObj );
//      array[i]->accept( aWcObj );
// o Get rid of compType, returnType(), Client.

#include <iostream.h>
enum compType { PrimitiveT, LinkT, CompositeT };

class Component {
public:
   virtual compType  returnType()       = 0;
   virtual void      streamOut()        = 0;
   virtual void      add( Component* )  { };
};

class Primitive : public Component {
public:
   Primitive( int id )   { identity = id; }
   compType returnType() { return PrimitiveT; }
   void     streamOut()  { cout << identity << " "; }
private:
   int identity;
};

class Link : public Component {
public:
   Link( Component& ele ) : linkElement(ele)  { }
   compType   returnType()                    { return LinkT; }
   void       streamOut()                     { linkElement.streamOut(); }
   Component& getSubject()                    { return linkElement; }
private:
   Component& linkElement;
};

class Composite : public Component {
public:
   Composite()                    { index = 0; }
   compType returnType()          { return CompositeT; }
   void     add( Component* ele ) { array[index++] = ele; }
   void     streamOut() {
      for (int i=0; i < index; i++)
         array[i]->streamOut();
   }
private:
   int         index;
   Component*  array[20];
};

class Client {
public:
   void cat( Component* node ) {
      if (node->returnType() == PrimitiveT) {
         cout << "cat: ";   node->streamOut();   cout << endl;
      } else if (node->returnType() == CompositeT)
         cout << "cat: Can't cat a directory." << endl;
      else if (node->returnType() == LinkT)
         cat(&(((Link*)node)->getSubject()));
   }
   void wc( Component* node ) {
      if (node->returnType() == PrimitiveT) {
          cout << "wc: ";   node->streamOut();   cout << endl;
      } else if (node->returnType() == CompositeT)
         cout << "wc: Can't wc a directory." << endl;
      else if (node->returnType() == LinkT)
         wc(&(((Link*)node)->getSubject()));
   }
};

void main( void ) {
   Composite        dir;
   Primitive        file1(1), file2(2);
   Link             alias( file1 );
   Component*       array[4];
   Client           doFile;
                    
   dir.add( &file1 );
   dir.add( &file2 );
   dir.add( &alias );
   dir.streamOut();
   cout << endl;

   array[0] = &dir;
   array[1] = &file1;
   array[2] = &file2;
   array[3] = &alias;
   for (int i = 0; i < 4; i++) {
      doFile.cat( array[i] );
      doFile.wc( array[i] );
}  }

// 1 2 1 
// cat: Can't cat a directory.
// wc: Can't wc a directory.
// cat: 1 
// wc: 1 
// cat: 2 
// wc: 2 
// cat: 1 
// wc: 1 
