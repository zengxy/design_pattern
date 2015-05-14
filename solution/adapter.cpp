// Purpose.  Adapter design pattern lab
// 
// Problem.  Simulated here is a "stack machine", or a non-OO
// implementation of a Stack class.  We would like to reuse this "legacy"
// asset as the basis for a new Queue class, but there is an "impedance
// mismatch" between the old and the new.
// 
// Assignment.
// o The class Queue should contain an "instance" of component Stack.
// o Queue needs a constructor, destructor, enque, deque, and isEmpty methods.  
//   Each of these methods will provide an adaptation from the Queue interface to the
//   Stack implementation.
// o If you map Queue's enque() to Stack's push(), then the pseudocode below
//   will give you insight into implementing Queue's deque() method.

//git push test


#include <iostream>
using namespace std;

struct StackStruct
{
	int*  array;
	int   sp;
	int   size;
};
typedef StackStruct Stack;

static void initialize( Stack* s, int size )
{
	s->array = new int[size];
	s->size = size;
	s->sp = 0;
}
static void cleanUp( Stack* s )
{
	delete s->array;
}
static int isEmpty( Stack* s )
{
	return s->sp == 0 ? 1 : 0;
}
static int isFull( Stack* s )
{
	return s->sp == s->size ? 1 : 0;
}
static void push( Stack* s, int item )
{
	if ( ! isFull(s)) s->array[s->sp++] = item;
}
static int pop( Stack* s )
{
	if (isEmpty(s))
		return 0;
	else
		return s->array[--s->sp];
}

class Queue {
	private:
		Stack* pstack;
		int size;
	public:
	Queue(int qsize)
	{
		size=qsize;
		pstack=new Stack;
		initialize(pstack,size);
	}

	~Queue()
	{
		cleanUp(pstack);
		delete pstack;
		pstack=NULL;
	}
	//mac test
	bool isFull()
	{
		if( ::isFull(pstack)==1 )
		{
			return true;
		}
		return false;
	}

	bool isEmpty()
	{
		if( ::isEmpty(pstack)==1 )
		{
			return true;
		}
		return false;
	}

	bool enque(int enqueNum)
	{
		if( this->isFull() )
			return false;

		push(pstack,enqueNum);
		return true;
	}

	int deque()
	{  
		Stack* ptemp=new Stack;
		initialize(ptemp,size);
		while( !::isEmpty(pstack) )
		{
			int temp=pop(pstack);
			push(ptemp,temp);
		}

		int out=pop(ptemp);

		while( !::isEmpty(ptemp) )
		{
			int temp=pop(ptemp);
			push(pstack,temp);
		}
		return out;
	}
};

int main() {
	Queue  queue(15);

	for (int i=0; i < 25; i++) queue.enque( i );
	while ( ! queue.isEmpty()) cout << queue.deque() << " ";
	cout << endl;
	return 1;
}
