// Purpose.  Abstract Factory design pattern lab.
// 
// Problem.  #ifdef case statements are spread throughout the code to
// accomodate 3 different porting targets.  This makes maintenance
// difficult, and porting to a 4th platform onerous.
// 
// Assignment.
// o Create an abstract base class Factory.
// o Define pure virtual member functions createSocket(), createPipe(),
//   and createThread().
// o Subclass UnixFactory, VmsFactory, and NtFactory off of Factory.
// o Refactor the "create" free functions to be member functions of one of
//   the Factory derived classes.
// o Declare a Factory* pointer local to main().
// o Use a single #ifdef case statement in main() to instantiate the desired
//   Factory derived class.
// o Do not optimize-out the doOneLaneIPC(), doTwoLaneIPC(), and
//   doParallelProcessing() free functions.
// o Pass the Factory pointer to each of these free functions so that they
//   can create sockets, pipes, and threads without regard to race, creed,
//   or platform.
// o Supply the desired "compiler directive" at compile time.
// o Extra credit: implement the Factory class as a Singleton.

#include <iostream>
using namespace std;

class Factory
{
   public:
      virtual void doOneLaneIPC()=0;
      virtual void doTwoLaneIPC()=0;
      virtual void doParallelProcessing()=0;
   private:
      virtual void createSocket()=0;
      virtual void createPipe()=0;
      virtual void createThread()=0;
};

class UnixFactory:public Factory
{
   public:
      void doOneLaneIPC(){this->createSocket();};
      void doTwoLaneIPC(){this->createPipe();};
      void doParallelProcessing(){this->createThread();};

   private:
      void createSocket() { std::cout << "Unix:createSocket:" << endl; };
      void createPipe()   { std::cout << "Unix:createPipe:" << endl; };
      void createThread() { std::cout << "Unix:createThread:" << endl; };
};

class VmsFactory:public Factory
{
   public:
      void doOneLaneIPC(){this->createSocket();};
      void doTwoLaneIPC(){this->createPipe();};
      void doParallelProcessing(){this->createThread();};

   private:
      void createSocket() { std::cout << "Vms:createSocket:" << endl; };
      void createPipe()   { std::cout << "Vms:createPipe:" << endl; };
      void createThread() { std::cout << "Vms:createThread:" << endl; };
}

class NtFactory:public Factory
{
   public:
      void doOneLaneIPC(){this->createSocket();};
      void doTwoLaneIPC(){this->createPipe();};
      void doParallelProcessing(){this->createThread();};
   
   private:
      void createSocket() { std::cout << "Nt:createSocket:" << endl; }
      void createPipe()   { std::cout << "Nt:createPipe:" << endl; }
      void createThread() { std::cout << "Nt:createThread:" << endl;};
}


void main( void ) {
   Factory * p;
#ifdef linux
   p=new UnixFactory();
#elif VMS
   p=new VmsFactory();
#elif NT
   p=new NtFactory();
#endif
   p->doOneLaneIPC();
   p->doTwoLaneIPC();
   p->doParallelProcessing();
   std::cout << "main: complete" << endl;
}