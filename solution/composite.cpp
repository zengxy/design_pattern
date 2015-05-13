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

#include <iostream>
using namespace std;
enum NodeType { LEAF, INTERIOR };

class Component
{
public:
    Component(int val,NodeType ntype)
    {
        value=val;
        type=ntype;
    }

    NodeType reportType()
    {
        return type;
    }
    virtual void traverse()=0;
protected:
    int       value;
    NodeType  type;

};




class Primitive:public Component
{
public:
    Primitive( int val ) :Component(val,LEAF){ }
    void     traverse()
    {
        cout << value << " ";
    }
};

class Composite:public Component
{
public:
    Composite( int val ) :Component(val,INTERIOR)
    {
        total = 0;
    }
    void    add( Component* c )
    {
        children[total++] = c;
    }
    void traverse()
    {
        cout << value << " ";
        for (int i=0; i < total; i++)
            children[i]->traverse();
       /* if (children[i]->reportType() == LEAF)
            ((Primitive*) children[i])->traverse();
        else
            children[i]->traverse();*/
}
private:
    int         total;
    Component*  children[99];
};

int main()
{
    Composite  first(1), second(2), third(3);

    first.add( &second );
    first.add( &third );
    first.add( (Composite*) new Primitive(4) );
    second.add( (Composite*) new Primitive(5) );
    second.add( (Composite*) new Primitive(6) );
    third.add( (Composite*) new Primitive(7) );
    first.traverse();
    cout << endl;
    return 1;
}

// 1 2 5 6 3 7 4
