// $Id: main.cc,v 1.2 2000/03/13 05:32:39 cs342 Exp $

#include "Sort_Viewer_Adapter.h"
#include "Sorter.h"
#include "Sort_Observer.h"
#include "create_sorter.cc"  /* For template instantiation of Factory Method */
#include <stdlib.h>  /* for rand () */
#include <iostream.h>
#include <assert.h>
#include <fstream.h>
#include <unistd.h>
#include "String.h"
#include <string.h>
#include "Connector.h"

// Includes for acceptor

// #include <fstream.h>  
// #include <iostream.h>
// #include <strstream.h>
// #include <string.h>  /* for memset () and strlen () */
// #include <unistd.h>  /* for close () and write () */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// #include "Sort_Info.h"
#include "Acceptor_Observer.h"
// #include "String.h"
// #include "Selection_Sort.h"
// #include "Quick_Sort.h" 
// #include "Merge_Sort.h"
// #include "Sorter.h"

// --------------------

class Java_Observer : public Sort_Observer
{
public:
  Sort_Viewer_Adapter sva;
  Java_Observer () {
  }
  virtual ~Java_Observer ();
  void update_sort (const Sort_Info_Base &sort_observation) {
    sva.Send(sort_observation);
  }
};

Java_Observer::~Java_Observer() 
{
}

class Main_Observer : public Sort_Observer
{
public:
  Main_Observer () {}
  virtual ~Main_Observer ();
  // Implementor functions.
  void update_sort (const Sort_Info_Base &sort_observation) {
    if (sort_observation.status () == Sort_Info_Base::SORTED) {
      sort_observation.print(cout);
    }
  }
};

Main_Observer::~Main_Observer ()
{
}

int client(char * sortfile)
{
  cout << "\nTesting the Merging of Arrays with hybridized sorting.\n" << endl;  
  Array<int> test1(20);
  for (size_t h = 0; h < 20; ++h) {
    test1.set(h, h);
  } 
  Array<int> test2(20);
  for (size_t f = 0; f < 20; ++f) {
    test2.set(f, f);
  }
  Array<int> test3(4);
  for (f = 0; f < 4; ++f) {
    test3.set(f, 20+f);
  }
  
  Array<Sort_Info<int>*> supertest(3);
  Sort_Info<int> sot1(Sort_Info_Base::QUICK_SORT, test1,
Sort_Info_Base::UNSORTED);
  Sort_Info<int> sot2(Sort_Info_Base::MERGE_SORT, test2,
Sort_Info_Base::UNSORTED);
  Sort_Info<int> sot3(Sort_Info_Base::SELECTION_SORT, test3,
Sort_Info_Base::UNSORTED);

  ofstream out1("out1.txt");
  sot1.print(out1);
  ofstream out2("out2.txt");
  sot2.print(out2);
  ofstream out3("out3.txt");
  sot3.print(out3);

  ifstream out1r("out1.txt");
  ifstream out2r("out2.txt");
  ifstream out3r("out3.txt");
  

  /*
  I added a Sort_Info constructor that takes in
  an istream and calls read to initialize the Sort_Info
  Object.
  This is a lot more convenient than creating a Sort_Info
  and then calling read on it. 
  */

  Sort_Info<int> sot1r(out1r);
  Sort_Info<int> sot2r(out2r);
  Sort_Info<int> sot3r(out3r);

  supertest.set(0, &sot1r);
  supertest.set(1, &sot2r);
  supertest.set(2, &sot3r);
  
  Merge_Sort<int>* howdy = new Merge_Sort<int>(supertest);
  Main_Observer mains;
  Java_Observer Jos;

  howdy->register_observer(mains);
  howdy->register_observer(Jos);
  
  howdy->start_sort();

  cout << "\nFinished Testing Super_Merge\n" << endl;
  
  Array<int> a1 (30);
  for (size_t i = 0; i < 30; ++i) {
    a1.set (i, ::rand ());
  }
  Sort_Info<int> sr1 (Sort_Info_Base::QUICK_SORT, a1);
  Sorter *s1 = create_sorter (sr1);
  
  Array<int> a2 (30);
  for (size_t j = 0; j < 30; ++j) {
    a2.set (j, ::rand ());
  }

  Sort_Info<int> sr2 (Sort_Info_Base::QUICK_SORT, a2);
  Sorter *s2 = create_sorter (sr2);
  
  cout << "Creating output filestream.\n" << endl;
  ofstream *output = new ofstream("out.txt");  
  
  cout << "\nPrinting Sort_Info sr1 to filestream.\n" << endl;
  sr1.print(*output);
  
  cout << "\nDeleting  output filestream.\n" << endl;
  delete output;
  
  cout << "\nCreating input filestream.\n" << endl;
  ifstream *input = new ifstream("out.txt");
  
  cout << "\nReading filestream into Sort_Info sr2.\n" << endl;
  sr2.read(*input);
  
  cout << "\nDeleting input filestream.\n" << endl;
  delete input;
  

  cout <<"\nTesting Print\n" << endl;
  cout <<"\n----------------------\n\n" << endl;
  cout <<"Printing S1\n" << endl;  
  sr1.print(cout);

  cout << "\nPrinting S2\n" << endl;
  sr2.print(cout);
  cout <<"\n----------------------\n" << endl;


  assert (s1 != 0);

  Main_Observer main_observer;
  Java_Observer java_observer;
  s1->register_observer (main_observer);
  s1->register_observer (java_observer);
  s1->start_sort ();

  delete s1;
 

  String teststr1("Hello");

  String teststr2("hello");

  teststr2 = teststr1;

  cout << teststr1 << endl;

  cout << teststr2 << endl;
 
  assert(teststr1 == teststr2);

  String teststr3("1234");

  String teststr4("4321");

  assert(teststr3 < teststr4);

  String teststr5(teststr4);

  assert(teststr4 != teststr5);

  Sort_Info<String> sis(Sort_Info_Base::QUICK_SORT, "new.txt",
Sort_Info_Base::UNSORTED);
  cout << " did we get here? " << endl;
  sis.print(cout);

  Sorter* stringsort = create_sorter(sis);

  Main_Observer mos;

  stringsort->register_observer(mos);

  stringsort->start_sort();

  delete stringsort;
  
  Sort_Info<String> sis2(Sort_Info_Base::QUICK_SORT, "new.txt",
Sort_Info_Base::UNSORTED);     

  Connector<String> con(sis2, "128.252.21.31", 6020);

  con.send_to_server();

  Array<String> aa;
  con.get_data(aa);

  Sort_Info<String> sottest(sis2.sort_type(), aa, Sort_Info_Base::SORTED);

  cout << "\nPrinting stream returned from server:\n" << endl;

  sottest.print(cout);

  Sort_Info<String> sis3(Sort_Info_Base::DISTRIBUTED_SORT,
  sortfile, Sort_Info_Base::UNSORTED);

  Sort_Info<String> sis4(Sort_Info_Base::QUICK_SORT, sortfile,
Sort_Info_Base::UNSORTED);

  Sorter *srt3 = create_sorter(sis3);
  Main_Observer mo;
  srt3->register_observer(mo);
  srt3->start_sort();

  delete srt3;

  Sorter *srt4 = create_sorter(sis4);
  Main_Observer mo2;
  srt4->register_observer(mo2);
  srt4->start_sort();     

  delete srt4;

  return 0;
}

const int SORT_SERVER_PORT = 6020;  /* Pick a slightly different
                                       constant, such as 3428. */
int
acceptor ()
{
  /* Open TCP socket. */
  int sockfd;

  if ((sockfd = ::socket (AF_INET, SOCK_STREAM, 0)) < 0) {
    perror ("socket");
    return -1;
  }

  /* Allow immediate reuse of the socket after the program ends. */
  int reuseaddr = 1;
  if ((::setsockopt (sockfd,
                     SOL_SOCKET,
                     SO_REUSEADDR,
                     &reuseaddr,
                     sizeof reuseaddr)) < 0) {
    perror ("SO_REUSEADDR");
    return -1;
  }

  /* Assign a name to the socket. */
  struct sockaddr_in serv_addr;
  ::memset ((char *) &serv_addr, 0, sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  serv_addr.sin_port = htons (SORT_SERVER_PORT);

  if (::bind (sockfd,
              (struct sockaddr *) &serv_addr,
              sizeof serv_addr) < 0) {
    perror ("bind");
    return -1;
  }

  /* Set the connection backlog. */
  ::listen (sockfd, 5);

  while (1) {
    /* Wait for a connection request . . . */
    struct sockaddr_in cli_addr;
    int clilen = sizeof (cli_addr);

    int newsockfd = ::accept (sockfd,
                              (struct sockaddr *) &cli_addr,
                              &clilen);
    if (newsockfd < 0) {
      perror ("accept");
      return -1;
    } else {
      //////
      cout << "Connection Accepted" << endl;
      fstream fs (newsockfd);

      Sort_Info<String> tempsi(fs, 1);

      Sorter* srt = create_sorter(tempsi);
 
      Acceptor_Observer<String> aos;

      srt->register_observer(aos);

      srt->start_sort();

      Array<String> sorted_data;

      aos.get_data(sorted_data);
      
      Sort_Info<String> returnval(tempsi.sort_type(), sorted_data,
Sort_Info_Base::SORTED);
      
      cout << "Server has finished processing data." << endl; 
      returnval.print(fs);
/*
      char buf[255];    
      int h = sorted_data.size();
      h >> fs;
      for (int j = 0; j < sorted_data.size(); ++j) {
        sorted_data[j] >> fs;
      }
*/
      close (newsockfd);
    }
  }

  if (close (sockfd)) {
    perror ("close");
    return -1;
  }

  return 0;
}

int
main (int argc, char *argv[])
{
  if (argc == 2) {
    int mode = ::strcmp(argv[1], "acceptor");
    if (mode == 0) {
      acceptor();
	} else {
	  cerr << "Invalid parameter combination." << endl;
	}
  } else if (argc == 3) {
     int mode = ::strcmp(argv[1], "client"); 
	client(argv[2]);
  } else {
     cout << "\n\n\nDistributed Sort v.325: " << endl;
     cout << "author: Ronnie Tam\n" << endl;
     cout << "Compiled on 3/25/2000\n" << endl;
     cout << "Syntax:" << endl;
     cout << "to launch client" << endl;
     cout << "         main client filename" << endl;
     cout << "to launch server" << endl;
     cout << "         main acceptor" << endl;
  }
  return 0;
}


#if defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  template class Sort_Info<char *>;
  template class Sort_Info<int>;
  template Sorter *create_sorter (const Sort_Info_Base &, const char * &);
  template Sorter *create_sorter (const Sort_Info_Base &, const int &);
#endif /* EXPLICIT_TEMPLATE_INSTANTIATION */
