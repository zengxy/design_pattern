// Purpose.  Command design pattern lab
// 
// Problem.  Encapsulation is an excellent tool for mitigating complexity.
// Here, the notion of a "command" has been designed that encapsulates a
// request to be performed on a "second party" object.  This encapsulating
// abstraction can now be handed to a "third party" object that provides
// some interesting "service" for the "first party" application.  As far as
// the Queue object is concerned, Command objects are opaque black boxes.
// This demo models the "first party" as really two separate entities: the
// entity responsible for "queueing up" Commands, and the entity responsible
// for "dequeueing" and executing commands.  The latter entity is obliged to
// "query" the type of each Command as it comes off the queue, and then step
// through a multiple branch conditional construct to identify the correct
// action to take.  Optimally, none of this would be necessary if the
// Command abstraction were appropriately "objectified".
// 
// Assignment.
// o Convert Command from a struct to a class
// o Remove the "type" field from the Command class
// o Add the following "pointer to member function" declaration to Command
//   "typedef void (File::* Action )();"
// o Add an "Action" private data member to Command
// o Replace the "unarchive", "transfer", and "compress" initialization
//   arguments with arguments of the form "&File::unarchive"
// o Add an execute() method to Command that simply calls action_ on receiver_
//   ( "(receiver_->*action_)()" )
// o Remove the "type query" expressions from main()
// o Replace the multiple branch conditional construct with a single call to
//   execute()

#include <iostream.h>
#include <string.h>

struct Command;

class Queue {
public:
   Queue() {
      add_ = remove_ = 0; }
   void enque( Command* c ) {
      array_[add_] = c;
      add_ = (add_ + 1) % SIZE; }
   Command* deque() {
      int temp = remove_;
      remove_ = (remove_ + 1) % SIZE;
      return array_[temp]; }
private:
   enum { SIZE = 10 };
   Command*  array_[SIZE];
   int       add_;
   int       remove_;
};

class File {
public:
   File( char* n ) { strcpy( name_, n ); }
   void unarchive() { cout << "unarchive " << name_ << endl; }
   void compress()  { cout << "compress "  << name_ << endl; }
   void transfer()  { cout << "transfer "  << name_ << endl; }
private:
   char  name_[30];
};

enum Action { unarchive, transfer, compress };

struct Command {
   Command( File* f, Action a ) { receiver = f; action = a; }
   File*   receiver;
   Action  action;
};

Command* input[8] = {
   new Command( new File("irImage.dat"),    unarchive ),
   new Command( new File("screenDump.jpg"), transfer ),
   new Command( new File("paper.ps"),       unarchive ),
   new Command( new File("widget.tar"),     compress ),
   new Command( new File("esmSignal.dat"),  unarchive ),
   new Command( new File("msword.exe"),     transfer ),
   new Command( new File("ecmSignal.dat"),  compress ),
   new Command( new File("image.gif"),      transfer )
};

void main( void )
{
   Queue     que;
   Command*  cmd;
   int       i;

   for (i=0; i < 8; i++)
      que.enque( input[i] );

   for (i=0; i < 8; i++)
   {
      cmd = que.deque();
      if (cmd->action == unarchive)
         cmd->receiver->unarchive();
      else if (cmd->action == transfer)
         cmd->receiver->transfer();
      else if (cmd->action == compress)
         cmd->receiver->compress();
   }
}

// unarchive irImage.dat
// transfer screenDump.jpg
// unarchive paper.ps
// compress widget.tar
// unarchive esmSignal.dat
// transfer msword.exe
// compress ecmSignal.dat
// transfer image.gif
