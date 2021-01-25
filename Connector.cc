#ifndef CONNECTOR_C
#define CONNECTOR_C

#include "Connector.h"

/*
This is the connector, It will do the following
1)Take an Array of type T in the constructor and an IP address
2)send_to_server() will cause the data to be sent to the IP via a stream
3)is_done() will return 0 or 1 based on whether the data has been returned
*/

template <class T>
Connector<T>::Connector(Sort_Info<T>& data, const char *const SERVER_HOST, 
const int SERVER_PORT)
  :SORT_SERVER_HOST_(SERVER_HOST),
   SORT_SERVER_PORT_(SERVER_PORT), 
   Data_(new Sort_Info<T>(data.sort_type(),data.data(),data.status()))
{
  if (Data_ == 0) 
     assert(! "Terminating, allocation failure.");
  /* Open TCP Socket */
  if ((sockfd = ::socket (AF_INET, SOCK_STREAM, 0)) < 0) {
    perror ("socket");
    assert(! "Socket problem.");
  }

  /* Assign a name to the socket. */
  ::memset ((char *) &serv_addr, 0, sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr (SORT_SERVER_HOST_);
  serv_addr.sin_port = htons (SORT_SERVER_PORT_);
  
  /* Connect to the server */
if ( ::connect (sockfd, (struct sockaddr *) &serv_addr, sizeof serv_addr)< 0)
    {
      perror ("connect");
      cerr << "The server on " << SORT_SERVER_HOST_ << ":" 
		<< SORT_SERVER_PORT_ << " is not up." << endl;
      assert(! "Connect failure.");
    }                           
}

template <class T>
void Connector<T>::send_to_server()
{
  fstream fs (sockfd);
  Data_->print(fs);
}

template <class T>
Connector<T>::~Connector()
{
  if (close (sockfd)) {
      perror ("close");
      assert(! "Problems closing socket.");
  }
  delete Data_;
} 

template <class T>
void Connector<T>::get_data(Array<T>& Sorted)
{
    fstream fst(sockfd);  
    Sort_Info<T> ss(fst, 1);
    Sorted = ss.data();
/*
    int temp;
    fs >> temp;
    Sorted = Array<T>(temp);
    char buf[255];
    fs.getline(buf,255);
    for (int i = 0; i < Sorted.size(); ++i) {
      fs.getline(buf, 255);
      Sorted[i] = String(buf);
    }
*/                                
}

#endif
