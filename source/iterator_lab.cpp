// Purpose.  Iterator design pattern lab
//
// Problem.  The BST class can traverse itself, but, the client of the BST
// cannot stop the traversal at will and interject application-specific
// functionality.  An Iterator class is a "partner" to a "container-like"
// class that provides the level of access and control that a client might
// need, while still maintaining the encapsulation of the original class.
// John Lakos has asserted that the interface of a "container-like" class
// is not "necessary and sufficient" until an Iterator capability is provided.
//
// Assignment.
// o Declare a class Iterator
// o The public interface of class Iterator should consist of -
//      Iterator( BST* );
//      void first();
//      void next();
//      int isDone();
//      Node& currentItem();
// o Make class Iterator a friend of class BST
// o Add the following method to class BST
//      Iterator* createIterator();
// o Add the following to the end of main() -
//      create an Iterator object
//      in a for loop, traverse the BST by using Iterator's first(), next(),
//         isDone(), and currentItem() methods
//      in a second for loop, traverse the BST again
//      deallocate the Iterator object
// o The BST::createIterator() implementation needs to create and return an
//   "appropriately initialized" instance of class Iterator
// o The school solution private data members of class Iterator are:
//      BST*    bst;
//      Node**  list;
//      int     nextNode;
// o A strategy for the Iterator::first() implementation is -
//      create a dynamic array of type Node* whose size is equal to the number
//         of nodes in the BST
//      traverse the BST, copying each Node* into the dynamic array (the array
//         will now "mirror" the BST)
//      initialize a "next array element" data member to 0
// o Traversing the BST to initialize the dynamic array could be implemented
//   by defining a recursive function that looks a lot like the current
//   BST::traverse(Node*) method.  The school solution implementation defines
//   the following private utility method -
//      void buildList( Node* current ) {
//         if (current->left != 0) buildList( current->left );
//         list[nextNode++] = current;
//         if (current->right != 0) buildList( current->right );
//      }
// o Iterator::next() simply increments the "next array element" data member
// o Iterator::currentItem() uses the "next array element" data member to
//   index into the dynamic array and then returns the dereferenced pointer
// o Iterator::isDone() needs an implementation
// o The dynamic array created in Iterator::first() needs to be deallocated if
//   a second call to Iterator::first() is made

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

struct Node {
   int value;  Node* left;  Node* right;
   Node() { left = right = 0; }
   friend ostream& operator<< ( ostream& os, Node& n ) { return os << n.value; }
};

class BST {
private:
   Node*  root;
   int    size;
public:
   BST() {
      root = 0;
   }
   void add( int in ) {
      if (root == 0) {
         root = new Node;
         root->value = in;
         size = 1;
         return;
      }
      add( in, root );
   }
   void traverse() { traverse( root ); }
private:
   void add( int in, Node* current ) {
      if (in < current->value)
         if (current->left == 0) {
            current->left = new Node();
            current->left->value = in;
            size++;
         }
         else add( in, current->left );
      else
         if (current->right == 0) {
            current->right = new Node();
            current->right->value = in;
            size++;
         }
         else add( in, current->right );
   }
   void traverse( Node* current ) {
      if (current->left != 0) traverse( current->left );
      cout << current->value << "  ";
      if (current->right != 0) traverse( current->right );
   }
};

void main( void ) {
   BST     bst;
   time_t  t;
   srand((unsigned) time(&t));

   cout << "original:  ";
   for (int i=0, val; i < 15; i++) {
      val = rand() % 49 + 1;
      cout << val << "  ";
      bst.add( val );
   }
   cout << "\ntraverse:  ";
   bst.traverse();
   cout << endl;
}

// original:  11  43  7  2  22  3  25  40  41  36  32  11  24  11  37
// traverse:  2  3  7  11  11  11  22  24  25  32  36  37  40  41  43
// Iterator:  2  3  7  11  11  11  22  24  25  32  36  37  40  41  43
// Iterator:  2  3  7  11  11  11  22  24  25  32  36  37  40  41  43
